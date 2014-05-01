#include "Play.h"
#include "PlayTree.h"

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

Play* Play::GetBestChild( PlayTree* playTree )
{
	if(!playTree || !playTree->possiblePlays || !playTree->possiblePlays->size())
		return NULL;

	Play* bestPlay = (*playTree->possiblePlays)[0]->currentPlay;

	for(int i = 0; i < playTree->possiblePlays->size(); i++)
	{
		if((*playTree->possiblePlays)[i]->currentPlay->score > bestPlay->score)
			bestPlay = (*playTree->possiblePlays)[i]->currentPlay;
	}

	return bestPlay;
}

Play* Play::GetWorstChild( PlayTree* playTree )
{
	if(!playTree || !playTree->possiblePlays || !playTree->possiblePlays->size())
		return NULL;

	Play* worstPlay = (*playTree->possiblePlays)[0]->currentPlay;

	for(int i = 0; i < playTree->possiblePlays->size(); i++)
	{
		if((*playTree->possiblePlays)[i]->currentPlay->score < worstPlay->score)
			worstPlay = (*playTree->possiblePlays)[i]->currentPlay;
	}

	return worstPlay;
}
