//***************************************************************************** 
// File name:	 TopObstacle.cpp
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Includes Functions for the TopObstacle Class
// Hours:      1 Hour
//*****************************************************************************

#include "TopObstacle.h"

const std::string TopObstacle::FILE_PATH = "assets\\toppipe.png";

/******************************************************************************
* Function:    TopObstacle
*
* Description: constructor for the TopObstacle
*
* Parameters:  int - Starting X position
*							 int - Which Y position to choose
*
* Returned:    none
******************************************************************************/
TopObstacle::TopObstacle(int startX, int heightChoice) : 
												 Obstacle(startX, FILE_PATH) {
  switch (heightChoice) {
	case 1:
	  setY(HEIGHT1 - getHeight());
	  break;
	case 2:
	  setY(HEIGHT2 - getHeight());
	  break; 
	case 3:
	  setY(HEIGHT3 - getHeight());
	  break;
  }
}