//****************************************************************************** 
// File name:	 Direction2D.cpp
// Author:		 Computer Science, Pacific University
// Date:		   4/4/2017
// Class:		   CS 250
// Assignment: SDL_MovingCircle
// Purpose:		 Implement a 2D direction
//******************************************************************************

#include "Direction2D.h"
#include <iostream>
#include <string>

// The following lookup table is used to help convert string directions to 
// an enum direction.

const std::string Direction2D::CompassDirectionNames[] =
{
	// 0    1     2    3     4    5     6    7
	"N", "NE", "E", "SE", "S", "NW", "W", "SW"
};

// The following lookup table is used to increment the current X and Y
// positions based on the direction of travel.

const int Direction2D::MoveLookup[][Direction2D::NUMBER_OF_COORDINATES] =
{
	{ 0, -1 },	// NORTH
	{ 1, -1 },	// NORTHEAST
	{ 1, 0 },		// EAST
	{ 1, 1 },		// SOUTHEAST
	{ 0, 1 },		// SOUTH
	{ -1, -1 },	// NORTHWEST
	{ -1, 0 },	// WEST
	{ -1, 1 }		// SOUTHWEST
};

// The following lookup table is used to determine the new direction for a
// reflection. For instance, if an object is moving N and hits the top edge,
// the new direction is S.

// Order is: Top, Right, Bottom, Left reflection of 1 of 8 directions where
// N = 0, NE = 1, E = 2, SE = 3, S = 4, NW = 5, W = 6, SW = 7
const int Direction2D::ReflectLookup[][Direction2D::NUMBER_OF_SIDES] =
{
	{ S,  X,  X,  X },		//N
	{ SE, NW, X,  X },	  //NE
	{ X,  W,  X,  X },		//E
	{ X,  SW, NE, X },    //SE
	{ X,  X,  N,  X },		//S
	{ SW, X,  X,  NE },   //NW
	{ X,  X,  X,  E },		//W
	{ X,  X,  NW, SE }	  //SW
};
//******************************************************************************
// Constructor:	Direction2D
//
// Description:	Initialize the Direction to the argument given
//
// Parameters:	eDirection - the direction to use
//
// Returned:		none
//******************************************************************************
Direction2D::Direction2D (CompassDirection eDirection)
{

	meCompassDirection = eDirection;

	setMoveByCompassDirection ();
}

//******************************************************************************
// Method:	    setMoveByCompassDirection
//
// Description:	Set the x and y movement based on the current 
//              compass direction
//
// Parameters:  none
//
// Returned:	  none
//******************************************************************************
void Direction2D::setMoveByCompassDirection ()
{
	const int X_CHANGE = 0;
	const int Y_CHANGE = 1;
	if (meCompassDirection < Direction2D::N || meCompassDirection > Direction2D::SW)
	{
		mXMove = 0;
	}
	mXMove = MoveLookup[meCompassDirection][X_CHANGE];
	mYMove = MoveLookup[meCompassDirection][Y_CHANGE];
}

//******************************************************************************
// Method:	    getCompassDirection
//
// Description:	get the current compass direction
//
// Parameters:  none
//
// Returned:	  the current compass direction
//******************************************************************************
Direction2D::CompassDirection Direction2D::getCompassDirection () const
{
	return meCompassDirection;
}

//******************************************************************************
// Method:	    reflectOnTop
//
// Description:	change the compass direction to reflect a bounce off the top
//              of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//******************************************************************************
Direction2D Direction2D::reflectOnTop () const
{
	return Direction2D (static_cast<Direction2D::CompassDirection>
		(ReflectLookup[meCompassDirection][TOP_SIDE]));
}

//******************************************************************************
// Method:	    reflectOnRightSide
//
// Description:	change the compass direction to reflect a bounce off the right
//              side of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//******************************************************************************
Direction2D Direction2D::reflectOnRightSide () const
{
	return Direction2D (static_cast<Direction2D::CompassDirection>
		(ReflectLookup[meCompassDirection][RIGHT_SIDE]));
}

//******************************************************************************
// Method:	    reflectOnBottom
//
// Description:	change the compass direction to reflect a bounce off the 
//              bottom of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//******************************************************************************
Direction2D Direction2D::reflectOnBottom () const
{
	return Direction2D (static_cast<Direction2D::CompassDirection>
		(ReflectLookup[meCompassDirection][BOTTOM_SIDE]));
}

//******************************************************************************
// Method:	    reflectOnLeftSide
//
// Description:	change the compass direction to reflect a bounce off the side
//              of the screen
//
// Parameters:  none
//
// Returned:	  the new compass direction
//******************************************************************************
Direction2D Direction2D::reflectOnLeftSide () const
{
	return Direction2D (static_cast<Direction2D::CompassDirection>
		(ReflectLookup[meCompassDirection][LEFT_SIDE]));
}

//******************************************************************************
// Method:	    getXMove
//
// Description:	get the current X move
//
// Parameters:  none
//
// Returned:	  the current X move
//******************************************************************************
int Direction2D::getXMove () const
{
	return mXMove;
}

//******************************************************************************
// Method:	    getYMove
//
// Description:	get the current Y move
//
// Parameters:  none
//
// Returned:	  the current Y move
//******************************************************************************
int Direction2D::getYMove () const
{
	return mYMove;
}

//******************************************************************************
// Function:	  operator>> (friend of the class)
//
// Description:	Read in a direction from the stream. The direction in the file
//              must be written as a string that matches a value in
//              Direction2D::CompassDirectionNames
//
// Parameters:  rcInStream  - the stream to read from
//              rcDirection - the direction to fill
//
// Returned:	  the modified stream read from
//******************************************************************************

std::istream& operator>>(std::istream &rcInStream, Direction2D &rcDirection)
{
	std::string compassDirection;

	rcInStream >> compassDirection;

	rcDirection.setCompassDirection (compassDirection);

	return rcInStream;
}

//******************************************************************************
// Method:	    setCompassDirection
//
// Description:	Set the compass direction based on a string that matches
//              a value in Direction2D::CompassDirectionNames and also
//              set the x and y move.
//
// Parameters:  compassDirection - the name of the direction
//
// Returned:	  none
//******************************************************************************
void Direction2D::setCompassDirection (std::string compassDirection)
{
	for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
	{
		if (CompassDirectionNames[i] == compassDirection)
		{
			meCompassDirection = static_cast<CompassDirection> (i);
		}
	}
	setMoveByCompassDirection ();
}
