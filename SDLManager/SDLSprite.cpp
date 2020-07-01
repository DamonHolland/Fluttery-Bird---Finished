//****************************************************************************** 
// File name:	 SDLSprite.h
// Author:		 Computer Science, Pacific University
// Date:		   4/4/2017
// Class:		   CS 250
// Assignment: Sprite
// Purpose:		 Implement a Sprite
//******************************************************************************
#include "SDLSprite.h"
#include "SDLManager.h"

/*******************************************************************************
* Constructor: SDLSprite
*
* Description: Load sprite
*
* Parameters:  spriteName - filename of the image
*              xCoord - x screen coordinate
*              yCoord - y screen coordinate
*
* Returned:    None
******************************************************************************/
SDLSprite::SDLSprite (std::string spriteName, int xCoord, int yCoord)
{
	SDLManager &rcSDLManager = SDLManager::instance ();
	SpriteDimensions sSpriteDimensions;

	//strcpy_s (mFileName, MAX_NAME_LEN, pszFileName);
	mSpriteName = spriteName;
	mXCoord = xCoord;
	mYCoord = yCoord;
	sSpriteDimensions = rcSDLManager.loadSprite (mSpriteName.c_str ());
	mHeight = sSpriteDimensions.height;
	mWidth = sSpriteDimensions.width;
}

/*******************************************************************************
* Destructor: SDLManager
*
* Description: Destruct the object
******************************************************************************/
SDLSprite::~SDLSprite ()
{
	
}

/*******************************************************************************
* Method:      getName
*
* Description: get the filename of the sprite
*
* Parameters:  none
*
* Returned:    the filename
******************************************************************************/

std::string SDLSprite::getName () const
{
	return mSpriteName;
}

/*******************************************************************************
* Method:      draw
*
* Description: draw the sprite on the screen
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void SDLSprite::draw () const
{
	SDLManager &rcSDLManager = SDLManager::instance ();
	rcSDLManager.drawSprite (*this);
}

/*******************************************************************************
* Method:      getX
*
* Description: get the x screen coordinate
*
* Parameters:  none
*
* Returned:    the x coordinate
******************************************************************************/
int SDLSprite::getX () const
{
	return mXCoord;
}

/*******************************************************************************
* Method:      getX
*
* Description: get the x screen coordinate
*
* Parameters:  none
*
* Returned:    the x coordinate
******************************************************************************/
int SDLSprite::getY () const
{
	return mYCoord;
}

/*******************************************************************************
* Method:      getX
*
* Description: xet the x screen coordinate
*
* Parameters:  int - the x coordinate
*
* Returned:    None
******************************************************************************/
void SDLSprite::setX (int xCoord)
{
	mXCoord = xCoord;
}

/*******************************************************************************
* Method:      getY
*
* Description: xet the y screen coordinate
*
* Parameters:  int - the y coordinate
*
* Returned:    None
******************************************************************************/
void SDLSprite::setY (int yCoord)
{
	mYCoord = yCoord;
}

//***************************************************************************
// Function:    setScale
//
// Description: Set the scaling factor for the Sprite.  
//
// Parameters:  scale - the scaling factor. 
//              1.0 is no change. <1.0 is shrink, >1.0 is expand
//
// Returned:    None
//***************************************************************************
void SDLSprite::setScale (double scale)
{
	mScale = scale;
}

//***************************************************************************
// Function:    setRotation
//
// Description: Set the angle of rotation of the sprite.
//
// Parameters:  rotation - the degrees of rotation, 0.0 to 359.0
//
// Returned:    None
//***************************************************************************
void SDLSprite::setRotation (double rotation)
{
	mRotationInDegrees = rotation;
}

//***************************************************************************
// Function:    getRotation
//
// Description: Get the angle of rotation of the sprite.
//
// Parameters:  None
//
// Returned:    the rotation of the sprite
//***************************************************************************
double SDLSprite::getRotation () const
{
	return mRotationInDegrees;
}

//***************************************************************************
// Function:    clicked
//
// Description: determine if the sprite has been clicked
//
// Parameters:  x - x coordinate of mouse click on screen
//              y - y coordinate of mouse click on screen
//
// Returned:    true if the x,y falls inside the sprite
//***************************************************************************
bool SDLSprite::clicked (int x, int y)
{
	bool bRetVal = false;
	if (x >= mXCoord && x <= mXCoord + mWidth &&
		y >= mYCoord && y <= mYCoord + mHeight)
	{
		bRetVal = true;
		//clickEventHandler ();
	}

	return bRetVal;
}

//***************************************************************************
// Function:    getWidth
//
// Description: Get the width
//
// Parameters:  None
//
// Returned:    the width
//***************************************************************************
int SDLSprite::getWidth () const
{
	return static_cast<int>(mWidth * mScale);
}

//***************************************************************************
// Function:    getHeight
//
// Description: Get the height
//
// Parameters:  None
//
// Returned:    the height
//***************************************************************************
int SDLSprite::getHeight () const
{
	return static_cast<int>(mHeight * mScale);
}
