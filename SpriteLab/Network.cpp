//***************************************************************************** 
// File name:	 Network.cpp
// Author:		 Damon Holland
// Date:		   8/20/2020
// Purpose:		 Includes Functions for the Network class
//*****************************************************************************

#include "Network.h"
#include <iostream>

/******************************************************************************
* Function:    Network
*
* Description: constructor for the network
*
* Parameters:  int size - the size of the network
*
* Returned:    none
******************************************************************************/
Network::Network(int size){
	//Set the size of the network, and fill the bird vector with the neccessary
	//amount of birds;
	mSize = size;
	mMaxSize = size;
	Player newBird;
	for (int i = 0; i < mSize; i++)
	{

		for (int j = 0; j < 4; j++)
		{
			double newRand = -1000 + (rand() % 2000);
			newRand /= 1000;
			newBird.setBias(j, newRand);
		}

		for (int j = 0; j < 15; j++)
		{
			double newRand = 1 + (rand() % 1000);
			newRand /= 1000;
			newBird.setWeight(j, newRand);
		}


		mvBirds.push_back(newBird);
	}

}

/******************************************************************************
* Function:    update
*
* Description: updates the network of players
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Network::update(double px, double pty, double pby) {

	double inputValues[4] = {1.0, 0.5, -1.0, -0.5};

	for (int i = 0; i < mSize; i++)
	{
		mvBirds.at(i).update();
	}

	//Calculate the output node for the network for each bird
	for (int i = 0; i < mSize; i++)
	{
		//Set Input Values
		inputValues[0] = mvBirds.at(i).getVel() / 10;
		//CHANGE THIS TO BE BASED ON NEXT OBSTACLE, NOT FIRST
		inputValues[1] = (abs(mvBirds.at(i).getX() - px) - 300) / 300;
		inputValues[2] = (abs(pty - mvBirds.at(i).getY()) - 360) / 360;
		inputValues[3] = (abs(pby - mvBirds.at(i).getY()) - 360) / 360;


		if (mvBirds.at(i).getNodeOutput(inputValues) >= 0.5)
		{
			mvBirds.at(i).fly();
		}

	}


	return;
}

/******************************************************************************
* Function:    getSize
*
* Description: returns the size of the network
*
* Parameters:  none
*
* Returned:    int - the size of the network
******************************************************************************/
int Network::getSize() {
	return mSize;
}

/******************************************************************************
* Function:    getBird
*
* Description: gets the specified bird at the index
*
* Parameters:  int i - the index of the bird
*
* Returned:    Player - the player object at the specified index (The Bird)
******************************************************************************/
Player Network::getBird(int i) {
		return mvBirds.at(i);
}

/******************************************************************************
* Function:    removeBird
*
* Description: removes the bird at the specified index
*
* Parameters:  int i - the index of the bird
*
* Returned:    none
******************************************************************************/
void Network::removeBird(int i)
{
	mvBirds.erase(mvBirds.begin() + i);
	mSize--;
	return;
}


/******************************************************************************
* Function:    createNewGeneration
*
* Description: Generates a new generation of birds
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Network::createNewGeneration()
{
	Player newBird;

	mvBirds.clear();

	for (int i = 0; i < mMaxSize; i++)
	{

		for (int j = 0; j < 4; j++)
		{
			double newRand = -1000 + (rand() % 2000);
			newRand /= 1000;
			newBird.setBias(j, newRand);
		}

		for (int j = 0; j < 15; j++)
		{
			double newRand = 1 + (rand() % 1000);
			newRand /= 1000;
			newBird.setWeight(j, newRand);
		}


		mvBirds.push_back(newBird);
		mSize++;
	}

	return;
}