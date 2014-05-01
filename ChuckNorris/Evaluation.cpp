#include "Evaluation.h"


Evaluation::Evaluation(void)
{
}


Evaluation::~Evaluation(void)
{
}

int Evaluation::EvaluateScore( Play* play )
{
	//TODO: Make it better :D
	if(!play)
		return 0;

	//Score already done
	if(play->score)
		return play->score;

	int whiteCount = BitBoard::PieceCount(play->playBitBoard->whitePieces);
	int blackCount = BitBoard::PieceCount(play->playBitBoard->blackPieces);

	play->score = (whiteCount - blackCount);

	return play->score;
}

void Evaluation::EvaluatePlayList( vector<Play*>* playList )
{
	if(!playList || !playList->size())
		return;

	for(int i = 0; i < playList->size(); i++)
	{
		EvaluateScore((*playList)[i]);
	}
}

void Evaluation::EvaluateTreeChildren( PlayTree* playTree )
{
	if(!playTree || !playTree->possiblePlays || !playTree->possiblePlays->size())
		return;

	for(int i = 0; i < playTree->possiblePlays->size(); i++)
	{
		EvaluateScore((*playTree->possiblePlays)[i]->currentPlay);
	}
}

int Evaluation::MiniMax( PlayTree* playTree, bool max )
{
	if(!playTree)
		return 0;

	if(!playTree->possiblePlays || !playTree->possiblePlays->size()) //Nao tem filhos
	{
		playTree->currentPlay->score = EvaluateScore(playTree->currentPlay);
		playTree->score = playTree->currentPlay->score;
		return playTree->score;
	}

	else if(max) //Arvore tem filhos, max
	{
		for(int i = 0; i < playTree->possiblePlays->size(); i++)
		{
			MiniMax((*playTree->possiblePlays)[i], false);
		}
		playTree->currentPlay->score = Play::GetBestChild(playTree)->score;
		playTree->score = playTree->currentPlay->score;
		return playTree->score;
	}

	else //Arvore tem filhos, min
	{
		for(int i = 0; i < playTree->possiblePlays->size(); i++)
		{
			MiniMax((*playTree->possiblePlays)[i], true);
		}
		playTree->currentPlay->score = Play::GetWorstChild(playTree)->score;
		playTree->score = playTree->currentPlay->score;
		return playTree->score;
	}
}
