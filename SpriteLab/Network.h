//***************************************************************************** 
// File name:	 Player.h
// Author:		 Damon Holland
// Date:		   8/20/2020
// Purpose:		 Contains the Network of birds
//*****************************************************************************

#pragma once
#include "Player.h"
#include <vector>
#include "Player.h"

class Network{
public:
	Network(int size);
	void update(double px, double pmy);
	int getSize();
	int getGeneration();
	Player getBird(int i);
	void createNewGeneration();
	void removeBird(int i);


private:
	int mSize;
	int mMaxSize;
	int mGeneration;
	std::vector<Player> mvBirds;
	std::vector<Player> mvBestBirds;

};