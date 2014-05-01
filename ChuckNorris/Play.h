#pragma once

#include "BitBoard.h"

class Play
{
public:

	BitBoard* playBitBoard;

	Coordinate origin;
	Coordinate destination;

	void SwapPlayCoordinates();

	Play(void);
	~Play(void);
};

