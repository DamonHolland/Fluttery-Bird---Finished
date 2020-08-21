//***************************************************************************** 
// File name:	 Obstacle.cpp
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Includes Functions for the Obstacle Class
// Hours:      2 Hours
//*****************************************************************************

#include "Obstacle.h"
#include <string>

using namespace std;

/******************************************************************************
* Function:    Obstacle
*
* Description: constructor for the Obstacle class
*
* Parameters:  int - Starting X position
*							 string - the file path for the sprite image
*
* Returned:    none
******************************************************************************/
Obstacle::Obstacle(int startX, std::string filePath) :
									 SDLSprite(filePath, startX, 0){
}

/******************************************************************************
* Function:    update
*
* Description: update the obstacle
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Obstacle::update(){
  setX(getX()-X_VEL);
  return;
}

/******************************************************************************
* Function:    render
*
* Description: updates the obstacle
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Obstacle::render(){
  draw();
  return;
 }

/******************************************************************************
* Function:    getFrontX
*
* Description: get the x coordinate of the top of the obstacle
*
* Parameters:  none
*
* Returned:    int - x position of the top of the obstacle
******************************************************************************/
int Obstacle::getFrontX() const{
  return getX();
}

/******************************************************************************
* Function:    getBackX
*
* Description: get the x coordinate of the back of the obstacle
*
* Parameters:  none
*
* Returned:    int - x position of the back of the obstacle
******************************************************************************/
int Obstacle::getBackX() const{
  return getX() + getWidth();
}

/******************************************************************************
* Function:    getTopY
*
* Description: get the y coordinate of the top of the obstacle
*
* Parameters:  none
*
* Returned:    int - y position of the top of the obstacle
******************************************************************************/
int Obstacle::getTopY() const{
  return getY();
}

/******************************************************************************
* Function:    getBottomY
*
* Description: get the y coordinate of the bottom of the obstacle
*
* Parameters:  none
*
* Returned:    int - y position of the bottom of the obstacle
******************************************************************************/
int Obstacle::getBottomY() const{
  return getY() + getHeight();
}

/******************************************************************************
* Function:    isOOB
*
* Description: is the obstacle out of screen bounds?
*
* Parameters:  int - x position of the minimum window X
*
* Returned:    bool - is the obstacle out of screen bounds?
******************************************************************************/
bool Obstacle::isOOB(int windowMin){
  return (getBackX() < windowMin);
}

/******************************************************************************
* Function:    justPassed
*
* Description: has the obstacle just been passed by the player?
*
* Parameters:  const int - X position of the player to check
*
* Returned:    bool - has the obstacle just been passed by the player?
******************************************************************************/
bool Obstacle::justPassed(const int checkX) {
	bool bJustPassed = false;

	if (!mbPassed)
	{
		if ((getBackX() - (getWidth() / 2)) <= checkX)
		{
			bJustPassed = true;
			mbPassed = true;
		}
	}

	return bJustPassed;
}