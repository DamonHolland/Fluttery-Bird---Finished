//***************************************************************************** 
// File name:	 Obstacle.h
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Header file for the Obstacle Class
// Hours:      1 Hour
//*****************************************************************************

#pragma once
#include "SDLManager.h"
#include <string>

class Obstacle : public SDLSprite{
  public:

    Obstacle(int startX, std::string filePath);
    void update();
    void render();
  
    int getFrontX() const;
    int getBackX() const;
    int getTopY() const;
    int getBottomY() const;
  
    bool isOOB(int windowMin = 0);

		bool justPassed(const int checkX);
		bool justCleared(const int checkX);
  
  private:

    static const int X_VEL = 4;
		bool mbPassed = false;
		bool mbCleared = false;

};
