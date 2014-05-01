#include "Play.h"


Play::Play(void)
{
	playBitBoard = NULL;
	origin = Coordinate(0,0);
	destination = Coordinate(0,0);
	score = 0;
}


Play::~Play(void)
{
}

void Play::SwapPlayCoordinates()
{
	this->origin.Swap();
	this->destination.Swap();
}

Play* Play::GetBestPlay( vector<Play*>* playList )
{
	if(!playList || !playList->size())
		return NULL;

	Play* bestPlay = (*playList)[0];

	for(int i = 1; i < playList->size(); i++)
	{
		if((*playList)[i]->score > bestPlay->score)
			bestPlay = (*playList)[i];
	}

	return bestPlay;
}
