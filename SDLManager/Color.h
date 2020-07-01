//****************************************************************************
// File name:	 Color.h
// Author:     Computer Science, Pacific University
// Date:       
// Class:      
// Assignment: 
// Purpose:    
//****************************************************************************
#pragma once

#include "SDL.h"
#include <iostream>

class Color
{
	public:

	static const int RGBA = 4;
	static const int R = 0;
	static const int G = 1;
	static const int B = 2;
	static const int A = 3;

	enum E_COLOR {
		BLACK, GRAY, SILVER, WHITE, MAROON, RED, OLIVE, YELLOW,
		GREEN, LIME, TEAL, AQUA, NAVY, BLUE, PURPLE, FUCHSIA
	};
	static Color getColor (E_COLOR eColor);

	Color (Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
	Color (E_COLOR eColor = BLACK);

	Uint8 getR () const;
	Uint8 getG () const;
	Uint8 getB () const;
	Uint8 getA () const;

	void setOpacity (float opacity);

	friend std::istream& operator >> (std::istream &rcInStream, Color &rcColor);

	private:
	Uint8 mR, mG, mB, mA;
	static const Uint8 maRGBA[][RGBA];
};
