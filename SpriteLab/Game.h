//***************************************************************************** 
// File name:	 Game.h
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Header file for the Fluttery Bird Game Class
// Hours:      1 Hour
//*****************************************************************************

#pragma once
#include <SDLManager.h>
#include "Player.h"
#include "Obstacle.h"
#include <vector>
#include "MovingBackground.h"

class Game {
public:

	Game(int windowW, int bestScore);
	~Game();
	void handleEvents(SDLManager &manager, SDL_Event event);
	void update(SDLManager &manager);
	void render(SDLManager &manager);
	bool isRunning() const;
	int getScore() const;

private:

	static const int NUM_PIPES = 3;

	int mWindowWidth;
	int pipeSpawnDistance;

	int mScore, mBestScore;
	bool mbNewHighScore;
	bool mbIsRunning;
	bool mbIsPaused;
	bool mbGameOver;
	Player mcPlayer[50];
	int mNumPlayers = 50;
	std::vector<Obstacle*> mvpcObstacles;

	//Background sprites
	MovingBackground *mpcBackground;
	MovingBackground *mpcBackground2;

	//Menu Sprites
	SDLSprite *mpcGameOverMenu = new SDLSprite("assets\\gameover.png", 160, 200);
	SDLSprite *mpcNewHighScore = new SDLSprite("assets\\newscore.png", 430, 450);
	//Beginning Click Sprite
	SDLSprite *mpcClick = new SDLSprite("assets\\clicktostart.png", 200, 290);

};