#pragma once

#include "BitBoard.h"
#include <vector>

using namespace std;

class Play
{
public:

	BitBoard* playBitBoard;

	Coordinate origin;
	Coordinate destination;

	int score;

	void SwapPlayCoordinates();

	static Play* GetBestPlay(vector<Play*>* playList);

	Play(void);
	~Play(void);
};

