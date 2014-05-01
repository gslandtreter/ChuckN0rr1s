#include "PlayTree.h"

#include "Play.h"

PlayTree::PlayTree(void)
{
	currentPlay = NULL;
	possiblePlays = NULL;
	score = 0;
}


PlayTree::~PlayTree(void)
{
	if(currentPlay)
		delete currentPlay;

	if(possiblePlays)
	{
		for(int i = 0; i < possiblePlays->size(); i++)
		{
			delete (*possiblePlays)[i];
		}
		delete possiblePlays;
	}
}
