//****************************************************************************** 
// File name:	 SDLMovingSprite.h
// Author:		 Computer Science, Pacific University
// Date:		   4/4/2017
// Class:		   CS 250
// Assignment: Moving Sprite
// Purpose:		 Implement a Moving Sprite
//******************************************************************************

#pragma once

#include "SDLSprite.h"
#include "Direction2D.h"

class SDLMovingSprite : public SDLSprite
{
public:
	SDLMovingSprite (std::string spriteName, int xCoord, int yCoord, 
									 const Direction2D &rcDirection);
	void update ();

protected:
	Direction2D mcDirection;
};