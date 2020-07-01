//****************************************************************************** 
// File name:	 SDLMovingSprite.cpp
// Author:		 Computer Science, Pacific University
// Date:		   4/4/2017
// Class:		   CS 250
// Assignment: Moving Sprite
// Purpose:		 Implement a Moving Sprite
//******************************************************************************

#include "SDLMovingSprite.h"
#include "SDLManager.h"
#include <iostream>

/*******************************************************************************
* Constructor: SDLMovingSprite
*
* Description: Construct the Sprite
*
* Parameters:   spriteName - file name
*               xCoord - x screen coordinate
*               yCoord - y screen coordinate
*               rcDirection - movement direction
*
*
* Returned:    None
******************************************************************************/
SDLMovingSprite::SDLMovingSprite (std::string spriteName, int xCoord,
	int yCoord, const Direction2D &rcDirection = Direction2D::E) :
	SDLSprite (spriteName, xCoord, yCoord), mcDirection (rcDirection)
{

}

/*******************************************************************************
* Method:      update
*
* Description: Move the sprite based on direction
*
* Parameters:  None
*
* Returned:    None
******************************************************************************/
void SDLMovingSprite::update ()
{
	if (getY () <= 0)
	{
		mcDirection = mcDirection.reflectOnTop ();
	}

	if (getX () + getWidth () >= SDLManager::instance ().windowWidth ())
	{
		mcDirection = mcDirection.reflectOnRightSide ();
	}

	if (getX () <= 0)
	{
		mcDirection = mcDirection.reflectOnLeftSide ();
	}

	if (getY () + getHeight () >= SDLManager::instance ().windowHeight ())
	{
		mcDirection = mcDirection.reflectOnBottom ();
	}

	if (mcDirection.getCompassDirection () > Direction2D::SW)
	{
		int i = 0;
		++i;
	}
	setX (getX () + mcDirection.getXMove ());
	setY (getY () + mcDirection.getYMove ());
}