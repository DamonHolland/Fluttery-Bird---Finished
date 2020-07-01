//***************************************************************************** 
// File name:	 BottomObstacle.h
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Header file for the BottomObstacle Class
// Hours:      1 Hour
//*****************************************************************************

#pragma once
#include "Obstacle.h"

class BottomObstacle : public Obstacle {
public:

	BottomObstacle(int startX = 960, int heightChoice = 2);

private:

	static const std::string FILE_PATH;
	static const int HEIGHT1 = 256;
	static const int HEIGHT2 = 448;
	static const int HEIGHT3 = 640;

};