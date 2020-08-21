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
	mGeneration = 1;

	//Fill the network with randomized new birds
	Player newBird;
	for (int i = 0; i < mSize; i++)
	{
		newBird.randomize();
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
void Network::update(double px, double pmy) {

	double inputValues[2];

	for (int i = 0; i < mSize; i++)
	{
		mvBirds.at(i).update();
	}

	//Calculate the output node for the network for each bird
	for (int i = 0; i < mSize; i++)
	{
		//Set Input Values
		inputValues[0] = ((mvBirds.at(i).getX() - px) + 250) / 250;
		inputValues[1] = (mvBirds.at(i).getY() - pmy) / 560;

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
* Function:    getGeneration
*
* Description: returns the generation of the network
*
* Parameters:  none
*
* Returned:    int - the generation of the network
******************************************************************************/
int Network::getGeneration() {
	return mGeneration;
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
	//Remove the bird
	mvBirds.erase(mvBirds.begin() + i);
	mSize--;

	//If there is only 1 bird left, store it as the winner of it's generation if
	//It is better than any of the best birds
	if (mSize == 1)
	{
		if (mvBestBirds.size() <= 8)
		{
			mvBestBirds.push_back(mvBirds.at(0));
		}
		else
		{
			for (int i = 0; i < mvBestBirds.size(); i++)
			{
				if (mvBirds.at(0).getScore() > mvBestBirds.at(i).getScore())
				{
					mvBestBirds.at(i) = mvBirds.at(0);
					return;
				}
			}

		}
	}

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

	std::cout << mvBestBirds.size() << std::endl;

	//Include the best birds in the new generation
	for (int i = 0; i < mvBestBirds.size(); i++)
	{
		mvBirds.push_back(mvBestBirds.at(i));
		mSize++;
	}

	//Add new birds, breeded from the best
	for (int i = 0; i < mMaxSize - mvBestBirds.size(); i++)
	{
		newBird.breed(mvBestBirds);
		newBird.mutate(10);
		mvBirds.push_back(newBird);
		mSize++;
	}

	mGeneration++;

	return;
}