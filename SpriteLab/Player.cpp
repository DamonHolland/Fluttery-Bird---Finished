//***************************************************************************** 
// File name:	 Player.cpp
// Author:		 Damon and Isaac
// Date:		   5/6/2019
// Class:		   CS 250
// Purpose:		 Includes Functions for the Player Class
// Hours:      2 Hours
//*****************************************************************************

#include "Player.h"
#include <iostream>

const std::string Player::IMAGE_PATH = "assets\\bird.png";
const double Player::GRAVITY = 0.7;

/******************************************************************************
* Function:    Player
*
* Description: constructor for the player, calls the SDLSprite Constuctor with
*							 constant values
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
Player::Player() : SDLSprite(IMAGE_PATH, X_START, Y_START){
	//Initial Velocity
	mYVel = 0;

	//Set Neural Values
	for (int i = 0; i < m_BIAS_SIZE; i++)
	{
		mNodeBiases.push_back(0.01);
	}

	for (int i = 0; i < m_WEIGHT_SIZE; i++)
	{
		mNodeWeights.push_back(0.01);
	}
}

/******************************************************************************
* Function:    update
*
* Description: updates the player
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Player::update() {
	//-------------------Neural Network-----------------------

	//Update position based on Y velocity
	setY(getY() + static_cast<int>(mYVel));

	//Rotate Sprite based on Y velocity
	setRotation(getRotation() + mYVel / COLLISION_LEEWAY);

	//Readjust for maximum rotation bounds
	if (mYVel >= 0) {
		if (getRotation() >= MAX_FALL_ROTATION) {
			setRotation(MAX_FALL_ROTATION);
		}
	}
	else if (getRotation() <= MAX_FLY_ROTATION) {
		setRotation(MAX_FLY_ROTATION);
	}

	//Update velocity based on gravity
	mYVel += GRAVITY;

	//Limit velocity to the maximum velocity
	if (mYVel >= MAX_VEL) {
		mYVel = MAX_VEL;
	}

	//Reset velocity and stop player if at the top of screen
	if (getY() <= 0) {
		setY(1);
		mYVel = 0;
	}

	return;
}

/******************************************************************************
* Function:    render
*
* Description: draw the player to the screen
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Player::render() {
	//Render texture
	SDLSprite::draw();
	return;
}

/******************************************************************************
* Function:    fly
*
* Description: makes the player fly
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Player::fly() {
	//Make player go flappy
	mYVel = FLY_VEL;
	return;
}

/******************************************************************************
* Function:    touchingGround
*
* Description: Is the player touching the bottom of the screen?
*
* Parameters:  int - Y position of the bottom of the screen
*
* Returned:    bool - if the player is touching the bottom of the screen
******************************************************************************/
bool Player::touchingGround(int maxY) const {
	//Did player go crashy?
	bool bIsOut = false;

	if (getY() + getHeight() > maxY) {
		bIsOut = true;
	}

	return bIsOut;
}

/******************************************************************************
* Function:    isTouching
*
* Description: is the player touching the given obstacle?
*
* Parameters:  Obstacle* - pointer to an obstacle
*
* Returned:    bool - is the player touching the given obstacle?
******************************************************************************/
bool Player::isTouching(Obstacle* pObstacle) const {
	//Did player go crashy? pt COLLISION_LEEWAY
	//Check EACH corner to see if it is within the obstacle
	return ((getX() + COLLISION_LEEWAY) > pObstacle->getFrontX()
		&& (getX() + COLLISION_LEEWAY) < pObstacle->getBackX()
		&& (getY() + COLLISION_LEEWAY) > pObstacle->getTopY()
		&& (getY() + COLLISION_LEEWAY) < pObstacle->getBottomY())
		//Top Left//
		||

		((getX() + getWidth() - COLLISION_LEEWAY) > pObstacle->getFrontX()
		&& (getX() + getWidth() - COLLISION_LEEWAY) < pObstacle->getBackX()
		&& (getY() + COLLISION_LEEWAY) > pObstacle->getTopY()
		&& (getY() + COLLISION_LEEWAY) < pObstacle->getBottomY())
		//Top Right//
		||

		((getX() + COLLISION_LEEWAY) > pObstacle->getFrontX()
			&& (getX() + COLLISION_LEEWAY) < pObstacle->getBackX()
			&& (getY() + getHeight() - COLLISION_LEEWAY) > pObstacle->getTopY()
			&& (getY() + getHeight() - COLLISION_LEEWAY) < pObstacle->getBottomY())
		//Bottom Left
		||

		((getX() + getWidth() - COLLISION_LEEWAY) > pObstacle->getFrontX()
			&& (getX() + getWidth() - COLLISION_LEEWAY) < pObstacle->getBackX()
			&& (getY() + getHeight() - COLLISION_LEEWAY) > pObstacle->getTopY()
			&& (getY() + getHeight() - COLLISION_LEEWAY) < pObstacle->getBottomY());
		//Bottom Right
}

/******************************************************************************
* Function:    getVel
*
* Description: return the velocity of the player
*
* Parameters:  none
*
* Returned:    double - the velocity of the player
******************************************************************************/
double Player::getVel() const
{
	return mYVel;
}

/******************************************************************************
* Function:    setScore
*
* Description: Sets the score for the player
*
* Parameters:  int score - the score to set
*
* Returned:    none
******************************************************************************/
void Player::setScore(int score)
{
	mScore = score;
	return;
}

/******************************************************************************
* Function:    getScore
*
* Description: Gets the score for the player
*
* Parameters:  none
*
* Returned:    int - the score for the player
******************************************************************************/
int Player::getScore() const
{
	return mScore;
}

/******************************************************************************
* Function:    SetBias
*
* Description: Sets the bias for the node at the given index
*
* Parameters:  int i - the index of the node to set the value of
*							 double v - the new bias value for the node
* Returned:    none
******************************************************************************/
void Player::setBias(int i, double v)
{
		mNodeBiases[i] = v;
		return;
}

/******************************************************************************
* Function:    SetWeight
*
* Description: Sets the weight for the connection at the given index
*
* Parameters:  int i - the index of the conection to set the value of
*							 double v - the new weight value for the connection
* Returned:    none
******************************************************************************/
void Player::setWeight(int i, double v)
{
	mNodeWeights[i] = v;
	return;
}

/******************************************************************************
* Function:    getNodeOutput
*
* Description: Calculates the double for the output Node
*
* Parameters:  double inputs[4] - the array of inputs
* Returned:    double - the output of the final node
******************************************************************************/
double Player::getNodeOutput(std::vector<double> inputs)
{
	double output;

	//HiddenNodeLayer
	std::vector<double> hiddenNodes;

	for (int i = 0; i < m_BIAS_SIZE - 1; i++)
	{
		hiddenNodes.push_back(mNodeBiases[i]);
	}

	for (int i = 0; i < m_BIAS_SIZE - 1; i++)
	{
		for (size_t j = 0; j < inputs.size(); j++)
		{
			hiddenNodes.at(i) += inputs[j] * mNodeWeights[(m_BIAS_SIZE - 1) * j];
		}

		//Hidden Node Activation Function
		hiddenNodes.at(i) = tanh(hiddenNodes.at(i));
	}



	//output Node
	output = mNodeBiases[m_BIAS_SIZE - 1];

	for (int i = 0; i < m_BIAS_SIZE - 1; i++)
	{
		output += (hiddenNodes.at(i) * mNodeWeights[(m_BIAS_SIZE - 1) + i + 1]);
	}

	//Output Activation Function
	output = tanh(output);

	return output;
}

/******************************************************************************
* Function:    breed
*
* Description: Will set the attributes of this bird to a random combination
							 of other bird's attributes from a vector
*
* Parameters:  vector<Player> bestBirds - vector of the best birds
* Returned:    none
******************************************************************************/
void Player::breed(std::vector<Player> bestBirds)
{
	std::vector<Player> vBestBirds = bestBirds;
	//Fill the best birds vector with random birds, if there are not at least 8
	while (vBestBirds.size() < 8)
	{
		Player newBird;
		newBird.randomize();
		vBestBirds.push_back(newBird);
	}

	for (int i = 0; i < m_BIAS_SIZE; i++)
	{
		int random = rand() % 8;
		mNodeBiases[i] = vBestBirds.at(random).mNodeBiases[i];
	}

	for (int i = 0; i < m_WEIGHT_SIZE; i++)
	{
		int random = rand() % 8;
		mNodeWeights[i] = vBestBirds.at(random).mNodeWeights[i];
	}
	
	return;
}

/******************************************************************************
* Function:    mutate
*
* Description: Will mutate the attributes of the bird by a certain amount
*
* Parameters:  int rate - the amount to mutate by, random between 0 - rate
							 double amount - the amount to mutate by between 0 - amount
* Returned:    none
******************************************************************************/
void Player::mutate(int rate)
{
	//Randomly Mutate Biases
	for (int i = 0; i < m_BIAS_SIZE; i++)
	{
		if (rand() % rate == 0)
		{
			double newRand = (rand() % 200) - 100;
			newRand /= 100;
			mNodeBiases[i] += newRand;
		}
	}

	//Randomly Mutate Weights
	for (int i = 0; i < m_WEIGHT_SIZE; i++)
	{
		if (rand() % rate == 0)
		{
			double newRand = (rand() % 200) - 100;
			newRand /= 100;
			mNodeWeights[i] += newRand;
		}
	}
	return;
}

/******************************************************************************
* Function:    randomize
*
* Description: Will Randomize the attributes of the bird
*
* Parameters:  none
* Returned:    none
******************************************************************************/
void Player::randomize()
{

	for (int i = 0; i < m_BIAS_SIZE; i++)
	{
		double newRand = (rand() % 200) - 100;
		newRand /= 100;
		mNodeBiases[i] = newRand;
	}

	for (int i = 0; i < m_WEIGHT_SIZE; i++)
	{
		double newRand = (rand() % 200) - 100;
		newRand /= 100;
		mNodeWeights[i] = newRand;
	}

	return;
}