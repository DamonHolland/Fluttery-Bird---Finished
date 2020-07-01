#include "MovingBackground.h"

MovingBackground::MovingBackground(std::string spriteName, int xCoord,
																	 int yCoord, int speed) :
																	 SDLSprite(spriteName, xCoord, yCoord) {
	mScrollSpeed = speed;
}

void MovingBackground::update() {

	//Move Background left at specified speed
	setX(getX() - mScrollSpeed);

	//Reset Position if reached the end
	if (getX() <= -getWidth() / 2 ) {
		setX(0);
	}

	return;
}

void MovingBackground::render() {
	draw();
}
