#include "BitBoard.h"


BitBoard::BitBoard(void)
{
	this->whitePawns = 0;
	this->whiteRooks = 0;
	this->whiteBishops = 0;
	this->whitePieces = 0;

	this->blackPawns = 0;
	this->blackRooks = 0;
	this->blackBishops = 0;
	this->blackPieces = 0;

	this->fullBoard = 0;
	this->emptySpaces = UNIVERSE;
}


BitBoard::~BitBoard(void)
{
}

void BitBoard::PrintBitBoard( bitBoard_t bitBoard )
{
	bitBoard_t copy = bitBoard;
	bitBoard_t set = 0;

	for (int i = 0; i < 64; i++)
	{
		set = copy & 1;
		copy >>= 1;

		if((i % 8) == 0)
			printf("\n");

		printf("%d", set);
	}

	printf("\n");
	//Bad code, works for debuggin'.
}

BitBoard* BitBoard::Generate( GameState* gameState )
{
	if(!gameState)
		return NULL;

	BitBoard* newBitBoard = new BitBoard();

	const char* boardString = gameState->board.c_str();
	
	//Begin filling bitboard
	for(int i = 0; i < 64; i++)
	{
		switch(boardString[i])
		{
		case 'p':
			newBitBoard->whitePawns += 1;
			break;
		case 'r':
			newBitBoard->whiteRooks += 1;
			break;
		case 'b':
			newBitBoard->whiteBishops += 1;
			break;

		case 'P':
			newBitBoard->blackPawns += 1;
			break;
		case 'R':
			newBitBoard->blackRooks += 1;
			break;
		case 'B':
			newBitBoard->blackBishops += 1;
			break;
		}

		if(i < 63)
		{
			//Shift them bitboards dude
			newBitBoard->whitePawns <<= 1;
			newBitBoard->whiteRooks <<= 1;
			newBitBoard->whiteBishops <<= 1;

			newBitBoard->blackPawns <<= 1;
			newBitBoard->blackRooks <<= 1;
			newBitBoard->blackBishops <<= 1;
		}
	}

	//Bitwise OR operator FTW.
	newBitBoard->whitePieces = newBitBoard->whitePawns | newBitBoard->whiteRooks | newBitBoard->whiteBishops;
	newBitBoard->blackPieces = newBitBoard->blackPawns | newBitBoard->blackRooks | newBitBoard->blackBishops;

	newBitBoard->fullBoard = newBitBoard->whitePieces | newBitBoard->blackPieces;

	newBitBoard->emptySpaces = UNIVERSE ^ newBitBoard->fullBoard;

	//TODO: TURN DAT DEBUG OFF!
	BitBoard::PrintBitBoard(newBitBoard->emptySpaces);
}
