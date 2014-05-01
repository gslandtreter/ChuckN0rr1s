#pragma once


#include "BitBoard.h"
#include <vector>

using namespace std;

class PlayTree;

class Play
{
public:

	BitBoard* playBitBoard;

	Coordinate origin;
	Coordinate destination;

	int score;

	void SwapPlayCoordinates();

	static Play* GetBestPlay(vector<Play*>* playList);
	static Play* GetBestChild(PlayTree* playtree);
	static Play* GetWorstChild(PlayTree* playtree);

	Play(void);
	~Play(void);
};

