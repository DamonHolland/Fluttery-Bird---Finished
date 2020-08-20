//***************************************************************************** 
// File name:	 Player.cpp
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Includes Functions for the Player Class
// Hours:      2 Hours
//*****************************************************************************

#include "Player.h"
#include <iostream>

const std::string Player::IMAGE_PATH = "assets\\bird.png";
const double Player::GRAVITY = 0.5;

/******************************************************************************
* Function:    Player
*
* Description: constructor for the player, calls the SDLSprite Constuctor with
*							 constant values
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
Player::Player() : SDLSprite(IMAGE_PATH, X_START, Y_START){
	//Initial Velocity
	mYVel = rand() % 10 - 5;
}

/******************************************************************************
* Function:    update
*
* Description: updates the player
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Player::update() {

	//Update position based on Y velocity
	setY(getY() + static_cast<int>(mYVel));

	//Rotate Sprite based on Y velocity
	setRotation(getRotation() + mYVel / COLLISION_LEEWAY);

	//Readjust for maximum rotation bounds
	if (mYVel >= 0) {
		if (getRotation() >= MAX_FALL_ROTATION) {
			setRotation(MAX_FALL_ROTATION);
		}
	}
	else if (getRotation() <= MAX_FLY_ROTATION) {
		setRotation(MAX_FLY_ROTATION);
	}

	//Update velocity based on gravity
	mYVel += GRAVITY;

	//Limit velocity to the maximum velocity
	if (mYVel >= MAX_VEL) {
		mYVel = MAX_VEL;
	}

	//Reset velocity and stop player if at the top of screen
	if (getY() <= 0) {
		setY(1);
		mYVel = 0;
	}

	return;
}

/******************************************************************************
* Function:    render
*
* Description: draw the player to the screen
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Player::render() {
	//Render texture
	SDLSprite::draw();
	return;
}

/******************************************************************************
* Function:    fly
*
* Description: makes the player fly
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Player::fly() {
	//Make player go flappy
	mYVel = FLY_VEL;
	return;
}

/******************************************************************************
* Function:    touchingGround
*
* Description: Is the player touching the bottom of the screen?
*
* Parameters:  int - Y position of the bottom of the screen
*
* Returned:    bool - if the player is touching the bottom of the screen
******************************************************************************/
bool Player::touchingGround(int maxY) const {
	//Did player go crashy?
	bool bIsOut = false;

	if (getY() + getHeight() > maxY) {
		bIsOut = true;
	}

	return bIsOut;
}

/******************************************************************************
* Function:    isTouching
*
* Description: is the player touching the given obstacle?
*
* Parameters:  Obstacle* - pointer to an obstacle
*
* Returned:    bool - is the player touching the given obstacle?
******************************************************************************/
bool Player::isTouching(Obstacle* pObstacle) const {
	//Did player go crashy? pt COLLISION_LEEWAY
	//Check EACH corner to see if it is within the obstacle
	return ((getX() + COLLISION_LEEWAY) > pObstacle->getFrontX()
		&& (getX() + COLLISION_LEEWAY) < pObstacle->getBackX()
		&& (getY() + COLLISION_LEEWAY) > pObstacle->getTopY()
		&& (getY() + COLLISION_LEEWAY) < pObstacle->getBottomY())
		
		||

		((getX() + getWidth() - COLLISION_LEEWAY) > pObstacle->getFrontX()
		&& (getX() + getWidth() - COLLISION_LEEWAY) < pObstacle->getBackX()
		&& (getY() + COLLISION_LEEWAY) > pObstacle->getTopY()
		&& (getY() + COLLISION_LEEWAY) < pObstacle->getBottomY())

		||

		((getX() + COLLISION_LEEWAY) > pObstacle->getFrontX()
			&& (getX() + COLLISION_LEEWAY) < pObstacle->getBackX()
			&& (getY() + getHeight() - COLLISION_LEEWAY) > pObstacle->getTopY()
			&& (getY() + getHeight() - COLLISION_LEEWAY) < pObstacle->getBottomY())

		||

		((getX() + getWidth() - COLLISION_LEEWAY) > pObstacle->getFrontX()
			&& (getX() + getWidth() - COLLISION_LEEWAY) < pObstacle->getBackX()
			&& (getY() + getHeight() - COLLISION_LEEWAY) > pObstacle->getTopY()
			&& (getY() + getHeight() - COLLISION_LEEWAY) < pObstacle->getBottomY());
}