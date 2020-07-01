//***************************************************************************** 
// File name:	 TopObstacle.h
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Header file for the TopObstacle Class
// Hours:      1 Hour
//*****************************************************************************

#pragma once
#include "Obstacle.h"

class TopObstacle : public Obstacle{

  public:

	TopObstacle(int startX = 960, int heightChoice = 1);

  private:

	static const std::string FILE_PATH;

	static const int HEIGHT1 = 64;
	static const int HEIGHT2 = 256;
	static const int HEIGHT3 = 448;

};