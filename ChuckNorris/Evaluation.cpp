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
