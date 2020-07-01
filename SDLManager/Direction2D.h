//**************************************************************************** 
// File name:	 Direction2D.h
// Author:		 Computer Science, Pacific University
// Date:		   4/4/2017
// Class:		   CS 250
// Assignment: SDL_MovingCircle
// Purpose:		 Represent a two-dimensional direction
//*****************************************************************************

#pragma once

#include <iostream>

class Direction2D
{
public:
	static const int NUMBER_OF_DIRECTIONS = 8;
	static const int NUMBER_OF_SIDES = 4;
	static const int NUMBER_OF_COORDINATES = 2;

	enum CompassDirection
	{
		N, NE, E, SE, S, NW, W, SW, X
	};

	enum Side
	{
		TOP_SIDE, RIGHT_SIDE, BOTTOM_SIDE, LEFT_SIDE
	};

	static const std::string CompassDirectionNames[];
	static const int MoveLookup[][NUMBER_OF_COORDINATES];
	static const int ReflectLookup[][NUMBER_OF_SIDES];


	Direction2D (CompassDirection = N);

	Direction2D reflectOnLeftSide () const;
	Direction2D reflectOnRightSide () const;
	Direction2D reflectOnTop () const;
	Direction2D reflectOnBottom () const;

	int getXMove () const;
	int getYMove () const;

	CompassDirection getCompassDirection () const;

	friend std::istream& operator>> (std::istream& rcInStream, Direction2D &rcDirection);

private:
	CompassDirection meCompassDirection;
	int mXMove;
	int mYMove;

	void setCompassDirection (std::string compassDirection);
	void setMoveByCompassDirection ();

};
