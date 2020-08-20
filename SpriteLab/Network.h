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
	void update();
	int getSize();
	Player getBird(int i);
	void createNewGeneration();


private:
	int mSize;
	std::vector<Player> mvBirds;

};