//***************************************************************************** 
// File name:	 Game.cpp
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Includes Functions for the Fluttery Bird Game Class
// Hours:      3 Hours
//*****************************************************************************

#include "Game.h"
#include "TopObstacle.h"
#include "BottomObstacle.h"

/******************************************************************************
* Function:    Game
*
* Description: Constructor for the Game Class
*
* Parameters:  int - Width of Window
*							 int - best score of current session
*
* Returned:    none
******************************************************************************/
Game::Game(int windowW, int bestScore) {
	//Initial Conditions
	mWindowWidth = windowW;
	mBestScore = bestScore;
	mbIsRunning = true;
	mbIsPaused = false;
	mbGameOver = false;
	mbNewHighScore = false;
	mvpcObstacles.clear();

	mpcBackground = new MovingBackground("assets\\background.png", 0, 0, 1);
	mpcBackground2 = new MovingBackground("assets\\background2.png", 0, 577, 2);

	//Temporary Object to find the width of the pipes
	TopObstacle tempObstacle;
	//Calculate distance between initially created pipes
	pipeSpawnDistance = (mWindowWidth / NUM_PIPES) +
		(tempObstacle.getWidth() / NUM_PIPES);

	//Generate initial pipes
	for (int i = 0; i < NUM_PIPES; i++) {
		int pipeLevel = (rand() % 3) + 1;
		mvpcObstacles.push_back(new TopObstacle(mWindowWidth + 
														pipeSpawnDistance * (i - 1), pipeLevel));
		mvpcObstacles.push_back(new BottomObstacle(mWindowWidth + 
														pipeSpawnDistance * (i - 1), pipeLevel));
	}

}

/******************************************************************************
* Function:    ~Game
*
* Description: destructor for the game class / deletes pointers to objects
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
Game::~Game() {
	//Clean the memory of the obstacles in the vector
	for (size_t i = 0; i < mvpcObstacles.size(); i++) {
		delete mvpcObstacles.at(i);
	}
	mvpcObstacles.clear();

	delete mpcBackground;
	delete mpcGameOverMenu;
	delete mpcNewHighScore;
}

/******************************************************************************
* Function:    handleEvents
*
* Description: handle input from the user
*
* Parameters:  SDLManager - the manager for the game
*							 SDL_Event - the current event 
*
* Returned:    none
******************************************************************************/
void Game::handleEvents(SDLManager &manager, SDL_Event event) {

	//Window Close Event
	if (event.type == SDL_QUIT) {
			manager.animationStop();
		}

	//While Player has not lost
	if (mbGameOver) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			//Menu Button Pressed
			if (event.button.button == SDL_BUTTON_LEFT && event.key.repeat == 0 &&
				(event.button.x >= 522) && (event.button.x <= 627) && 
				(event.button.y >= 397) && (event.button.y <= 433) ) {
				mbIsRunning = false;
				manager.playSound("assets/button.wav", false);
			}
		}
	}

	return;
}

/******************************************************************************
* Function:    update
*
* Description: updates the game
*
* Parameters:  SDLManager - the manager for the game
*
* Returned:    none
******************************************************************************/
void Game::update(SDLManager &manager) {

	if (!mbIsPaused) {

		//Update Background
		mpcBackground->update();
		mpcBackground2->update();

		//Update Game Objects
		for(int i = 0; i < mNumPlayers;i++)
		{
			mcPlayer[i].update();
		}
		
		for (size_t i = 0; i < mvpcObstacles.size(); i++) {
			mvpcObstacles.at(i)->update();
		}

		//Respawn pipes when they exit the screen
		//Iterates by 2, because the pipes spawn in pairs
		for (size_t i = 0; i < mvpcObstacles.size(); i += 2) {
			if (mvpcObstacles.at(i)->isOOB()) {

				//deletes the objects and erases them from vector
				//NOTE: it uses "i" twice because the first is deleted
				delete mvpcObstacles.at(i);
				mvpcObstacles.erase(mvpcObstacles.begin() + i);
				delete mvpcObstacles.at(i);
				mvpcObstacles.erase(mvpcObstacles.begin() + i);

				//Create the new pipes
				int pipeLevel = (rand() % 3) + 1;
				mvpcObstacles.push_back(new TopObstacle(mWindowWidth, pipeLevel));
				mvpcObstacles.push_back(new BottomObstacle(mWindowWidth, pipeLevel));

			}
		}

		//Quit Game If Player Hits Ground
		bool bAllPlayersHit = true;
		for (int i = 0; i < mNumPlayers; i++)
		{
			if (!mcPlayer[i].touchingGround(manager.windowHeight()))
			{
				bAllPlayersHit = false;
			}
		}

		//Quit Game if Player Hits Obstacle
		for (int i = 0; i < mNumPlayers; i++)
		{
			for (size_t j = 0; j < mvpcObstacles.size(); j++) {
				if (mcPlayer[i].isTouching(mvpcObstacles.at(j))) {
					bAllPlayersHit = false;
				}
			}
		}

		//Quit if either tests were true
		if (bAllPlayersHit)
		{
			manager.playSound("assets/die.wav", false);
			mbGameOver = true;
			mbIsPaused = true;
		}

		//Check for score increase
		//ONLY CHECKS FIRST BIRD, CHANGE LATER
		for (size_t i = 0; i < mvpcObstacles.size(); i++) {
			if ((mvpcObstacles.at(i))->isPassed((mcPlayer[0].getX() +
					(mcPlayer[0].getWidth() / 2))) &&
				dynamic_cast<TopObstacle*>(mvpcObstacles.at(i)) != NULL) {
				mScore++;
				manager.playSound("assets/score.wav", false);
			};
			//Checks if an obstacle is passed and if it's a TopObstacle 
			//(to prevent doublecounting)
		}
	}
	else if (mbGameOver) {
		//Player will fall off of screen if they lose
		for (int i = 0; i < mNumPlayers; i++)
		{
			mcPlayer[i].update();
		}
	}

	return;
}

/******************************************************************************
* Function:    render
*
* Description: SDLManager - the manager for the game
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Game::render(SDLManager &manager) {


	//Clear Renderer
	manager.clearBackground();

	//Render Background
	mpcBackground->draw();
	mpcBackground2->draw();


	//Render the Click to Start Sprite
	if (mbIsPaused && !mbGameOver) {
		mpcClick->draw();
	}

	//Render Game Objects

	for (size_t i = 0; i < mvpcObstacles.size(); i++) {
		mvpcObstacles.at(i)->render();
	}

	for (int i = 0; i < mNumPlayers; i++)
	{
		mcPlayer[i].render();
	}

	//Render Score
	manager.displayText(480, 0, std::to_string(mScore), Color::WHITE, 2);

	//Draw Game Over Menu
	if (mbGameOver) {
		mpcGameOverMenu->draw();
		//Draw the score and best score
		manager.displayText(345, 380, std::to_string(mScore), Color::BLACK, 2);
		//If Score was beter than current best, set new best
		if (mScore > mBestScore) {
			mBestScore = mScore;
			mbNewHighScore = true;
		}
		//Render the New High Score Sprite if the player beat their high score
		if (mbNewHighScore) {
			mpcNewHighScore->draw();
		}
		manager.displayText(445, 380, std::to_string(mBestScore), Color::BLACK, 2);
	}

	//Present Renderer
	manager.render();
	return;
}

/******************************************************************************
* Function:    isRunning
*
* Description: is the game running?
*
* Parameters:  none
*
* Returned:    bool - is the game running?
******************************************************************************/
bool Game::isRunning() const {
	return mbIsRunning;
}

/******************************************************************************
* Function:    getScore
*
* Description: retrieve the score
*
* Parameters:  none
*
* Returned:    int - the current score
******************************************************************************/
int Game::getScore() const {
	return mScore;
}
