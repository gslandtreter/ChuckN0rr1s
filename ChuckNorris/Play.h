#pragma once

#include "BitBoard.h"

class Play
{
public:

	BitBoard* playBitBoard;

	Coordinate origin;
	Coordinate destination;

	Play(void);
	~Play(void);
};

