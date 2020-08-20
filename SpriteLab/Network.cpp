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
	Player newBird;
	for (int i = 0; i < mSize; i++)
	{
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
void Network::update() {

	for (int i = 0; i < mSize; i++)
	{
		mvBirds.at(i).update();
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
	mvBirds.clear();

	Player newBird;
	for (int i = 0; i < mSize; i++)
	{
		mvBirds.push_back(newBird);
	}
	return;
}