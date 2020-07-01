//***************************************************************************** 
// File name:	 driver.cpp
// Author:		 Computer Science Pacific University and Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Fluttery Bird Game Driver
// Hours:      1 Hour
//*****************************************************************************


#include "SDLManager.h"
#include "Game.h"
#include <ctime>


/******************************************************************************
* Function:    main
*
* Description: driver for the entire program
*
* Parameters:  int - SDL required main parameter
*							 char* - SDL required main parameter
*
* Returned:    int - Exit status
******************************************************************************/
int main (int argc, char *argv[])
{

	srand(static_cast<unsigned> (time(static_cast<time_t *>(NULL))));

	const std::string TITLE = "Fluttery Bird";
	const std::string VERDANA_FONT = "assets/flutterfont.ttf";
	const int FONT_SIZE = 80;

  int windowXPosition = SDL_WINDOWPOS_CENTERED,
		  windowYPosition = SDL_WINDOWPOS_CENTERED,
		  windowSizeX = 960,
      windowSizeY = 720;

  SDLManager &rcManager = SDLManager::instance ();
  SDL_Event uEvent;
  
  rcManager.initializeWorld (windowXPosition, windowYPosition,
														 windowSizeX, windowSizeY, TITLE.c_str(), 
															VERDANA_FONT, FONT_SIZE);


  rcManager.setBackgroundColor (Color::GRAY);
  rcManager.setForegroundColor (Color::WHITE);

  rcManager.animationStart ();
  rcManager.clearBackground ();

	//The Pointer to the game object
	Game *pcGame;
	//Best Score Tracker Across All Games
	int bestScore = 0;

	//Intro to game
	bool bGameStarted = false;
	//Create Intro Sprite And Render To Screen
	SDLSprite cIntro("assets\\intro.png", 0, 0);
	rcManager.clearBackground();
	cIntro.draw();
	rcManager.render();

	while (!bGameStarted) {

		if (rcManager.getSDLEvent(uEvent))
		{
			//Handle Start Button Press
			if (uEvent.type == SDL_MOUSEBUTTONDOWN) {
				if (uEvent.button.button == SDL_BUTTON_LEFT && uEvent.key.repeat == 0
					&& (uEvent.button.x >= 290) && (uEvent.button.x <= 633) &&
					(uEvent.button.y >= 251) && (uEvent.button.y <= 370)) {
					bGameStarted = true;
					rcManager.playSound("assets/button.wav", false);
				}
			}

			//Allow User to Quit Game From Intro Screen
			if (uEvent.type == SDL_QUIT) {
				bGameStarted = true;
				rcManager.animationStop();
			}

		}

	}

  //Loop for all game instances
	while (rcManager.animationIsRunning())
	{
		//Create new game object
		pcGame = new Game(rcManager.windowWidth(), bestScore);

		//Game loop for current game object
		while (pcGame->isRunning() && rcManager.animationIsRunning()) {

			pcGame->update(rcManager);
			pcGame->render(rcManager);

			if (rcManager.getSDLEvent(uEvent))
			{
				pcGame->handleEvents(rcManager, uEvent);
			}

		}

		//If the player broke their best score, set the new best score
		if (pcGame->getScore() > bestScore) {
			bestScore = pcGame->getScore();
		}

		//Delete game object
		delete pcGame;

	}

  return EXIT_SUCCESS;
}
