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

	std::vector<double> inputValues;

	for (int i = 0; i < mSize; i++)
	{
		mvBirds.at(i).update();
	}

	//Calculate the output node for the network for each bird
	for (int i = 0; i < mSize; i++)
	{
		inputValues.clear();

		//Set Input Values NORMALIZED
		//inputValues[0] = ((mvBirds.at(i).getX() - px) + 250) / 250;
		//inputValues[1] = (mvBirds.at(i).getY() - pmy) / 560;

		inputValues.push_back(mvBirds.at(i).getX() - px);
		inputValues.push_back(mvBirds.at(i).getY() - pmy);
		inputValues.push_back(mvBirds.at(i).getHeight());

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
Player* Network::getBird(int i) {
		return &mvBirds.at(i);
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
	//If this bird is a new best bird, add it to the best birds array
	if (mvBirds.size() <= 8)
	{
		if (mvBestBirds.size() < 8)
		{
			if (mvBirds.at(i).getScore() > 0)
			{
				mvBestBirds.push_back(mvBirds.at(i));
				std::cout << "New Best Bird With Score: " <<
										  mvBirds.at(i).getScore() << std::endl;
				printBestBirds();
			}
		}
		else
		{
			//Find the worst bird in the array
			int lowestIndex = 0, lowestScore = mvBestBirds.at(0).getScore();

			for (int j = 0; j < mvBestBirds.size(); j++)
			{
				if (mvBestBirds.at(j).getScore() < lowestScore)
				{
					lowestScore = mvBestBirds.at(j).getScore();
					lowestIndex = j;
				}
			}
			//Replace that bird with new bird if the new bird is better
			if (mvBirds.at(i).getScore() > lowestScore)
			{
				mvBestBirds.at(lowestIndex) = mvBirds.at(i);
				std::cout << "New Best Bird With Score: " <<
				mvBirds.at(i).getScore() << std::endl;
				printBestBirds();
			}

		}
	}


	//Remove the bird
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
		newBird.mutate(20);
		mvBirds.push_back(newBird);
		mSize++;
	}

	mGeneration++;

	return;
}

/******************************************************************************
* Function:    printBestBirds
*
* Description: Generates a new generation of birds
*
* Parameters:  none
*
* Returned:    none
******************************************************************************/
void Network::printBestBirds()
{
	std::cout << "Best Birds: ";
	for (int i = 0; i < mvBestBirds.size(); i++)
	{
		std::cout << mvBestBirds.at(i).getScore() << " ";
	}
	std::cout << std::endl;
	return;
}