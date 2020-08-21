//***************************************************************************** 
// File name:	 Player.h
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Header file for the Player Class
// Hours:      1 Hour
//*****************************************************************************

#pragma once
#include "SDLManager.h"
#include "Obstacle.h"

class Player : public SDLSprite{
public:

	Player();
	void update();
	void render();
	void fly();
	bool touchingGround(int maxY) const;
	bool isTouching(Obstacle* pObstacle) const;
	double getVel() const;
	void setScore(int score);
	int getScore() const;
	void setBias(int i, double v);
	void setWeight(int i, double v);
	double getNodeOutput(double inputs[2]);
	void breed(std::vector<Player> bestBirds);
	void mutate(int rate);
	void randomize();

	//Neural Network Information *****************************************
	//First 3 biases are hidden layer nodes, last value is the output node
	double mNodeBiases[4];
	//First 6 weights are connections from input nodes to hidden layer nodes
	//Last 3 weights are connections from hidden layer nodes to output nodes
	double mNodeWeights[9];
	//********************************************************************

private:

	double mYVel;
	int mScore;
	static const int X_START = 100;
	static const int Y_START = 320;
	static const int MAX_FALL_ROTATION = 45;
	static const int MAX_FLY_ROTATION = -45;
	static const int COLLISION_LEEWAY = 4;

	static const int FLY_VEL = -10;
	static const int MAX_VEL = 10;
	static const double GRAVITY;

	static const std::string IMAGE_PATH;

};