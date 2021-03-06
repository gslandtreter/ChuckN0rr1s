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

	int whiteBishops = BitBoard::PieceCount(play->playBitBoard->whiteBishops);
	int whiteRooks = BitBoard::PieceCount(play->playBitBoard->whiteRooks);

	int blackBishops = BitBoard::PieceCount(play->playBitBoard->blackBishops);
	int blackRooks = BitBoard::PieceCount(play->playBitBoard->blackRooks);

	int totalPieceDifference = whiteCount - blackCount;
	int bishopDifference = whiteBishops - blackBishops;
	int rookDifrerence = whiteRooks - blackRooks;

	int whitePawnSecond = BitBoard::PieceCount(play->playBitBoard->whitePawns & BitBoard::SECONDCOLUMN);
	int whitePawnThird = BitBoard::PieceCount(play->playBitBoard->whitePawns & BitBoard::THIRDCOLUMN);
	int whitePawnFourth= BitBoard::PieceCount(play->playBitBoard->whitePawns & BitBoard::FOURTHCOLUMN);
	int whitePawnFifth= BitBoard::PieceCount(play->playBitBoard->whitePawns & BitBoard::FIFTHCOLUMN);
	int whitePawnSixth = BitBoard::PieceCount(play->playBitBoard->whitePawns & BitBoard::SIXTHCOLUMN);
	int whitePawnSeventh = BitBoard::PieceCount(play->playBitBoard->whitePawns & BitBoard::SEVENTHCOLUMN);
	int whitePawnEighth = BitBoard::PieceCount(play->playBitBoard->whitePawns & BitBoard::EIGHTHCOLUMN);

	int pawnFraction = whitePawnSecond + (whitePawnThird * 2) +
		(whitePawnFourth * 3) + (whitePawnFifth * 4) + (whitePawnSixth * 20) + 
		(whitePawnSeventh * 30) + (whitePawnEighth * 50);

	play->score = pawnFraction + 6 * totalPieceDifference + 3 * bishopDifference + 2 * rookDifrerence;

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
