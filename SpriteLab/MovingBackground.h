#pragma once
#include <SDLSprite.h>

class MovingBackground : public SDLSprite{
public:
	MovingBackground(std::string spriteName, int xCoord, int yCoord, int speed);
	void update();
	void render();

private:
	int mScrollSpeed;

};