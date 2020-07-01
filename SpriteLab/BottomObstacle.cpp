//***************************************************************************** 
// File name:	 BottomObstacle.cpp
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Includes Functions for the BottomObstacle Class
// Hours:      1 Hour
//*****************************************************************************

#include "BottomObstacle.h"

const std::string BottomObstacle::FILE_PATH = "assets\\bottompipe.png";

/******************************************************************************
* Function:    BottomObstacle
*
* Description: constructor for the BottomObstacle
*
* Parameters:  int - Starting X position
*							 int - Which Y position to choose
*
* Returned:    none
******************************************************************************/
BottomObstacle::BottomObstacle(int startX, int heightChoice) :
															 Obstacle(startX, FILE_PATH) {
	switch (heightChoice) {
	case 1:
		setY(HEIGHT1);
		break;
	case 2:
		setY(HEIGHT2);
		break;
	case 3:
		setY(HEIGHT3);
		break;
	}
}