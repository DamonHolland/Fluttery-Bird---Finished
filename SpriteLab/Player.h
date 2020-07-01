//***************************************************************************** 
// File name:	 Player.h
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Header file for the Player Class
// Hours:      1 Hour
//*****************************************************************************

#pragma once
#include "SDLManager.h"
#include "Obstacle.h"

class Player : public SDLSprite{
public:

	Player();
	void update();
	void render();
	void fly();
	bool touchingGround(int maxY) const;
	bool isTouching(Obstacle* pObstacle) const;

private:

	double mYVel;
	static const int X_START = 100;
	static const int Y_START = 320;
	static const int MAX_FALL_ROTATION = 45;
	static const int MAX_FLY_ROTATION = -45;
	static const int COLLISION_LEEWAY = 4;

	static const int FLY_VEL = -10;
	static const int MAX_VEL = 10;
	static const double GRAVITY;

	static const std::string IMAGE_PATH;

};