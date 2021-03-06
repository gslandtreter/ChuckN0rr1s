#include "BitBoard.h"
#include "MoveGenerator.h"

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


bitBoard_t BitBoard::GoNorth( bitBoard_t currentBitBoard )
{
	return currentBitBoard >> 8;
}

bitBoard_t BitBoard::GoSouth( bitBoard_t currentBitBoard )
{
	return currentBitBoard << 8;
}

bitBoard_t BitBoard::GoEast( bitBoard_t currentBitBoard )
{
	return (currentBitBoard << 1) & notAFile;
}

bitBoard_t BitBoard::GoWest( bitBoard_t currentBitBoard )
{
	return (currentBitBoard >> 1) & notHFile;
}

bitBoard_t BitBoard::GoSouthWest( bitBoard_t currentBitBoard )
{
	return (currentBitBoard << 7) & notHFile;
}

bitBoard_t BitBoard::GoSouthEast( bitBoard_t currentBitBoard )
{
	return (currentBitBoard << 9) & notAFile;
}

bitBoard_t BitBoard::GoNorthWest( bitBoard_t currentBitBoard )
{
	return (currentBitBoard >> 9) & notHFile;
}

bitBoard_t BitBoard::GoNorthEast( bitBoard_t currentBitBoard )
{
	return (currentBitBoard >> 7) & notAFile;
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

Coordinate BitBoard::GetPieceCoordinate( bitBoard_t bitBoard )
{
	bitBoard_t copy = bitBoard;
	bitBoard_t set = 0;

	int row = 0, column = 0;
	for (int i = 0; i < 64; i++)
	{
		set = copy & 1;
		copy >>= 1;

		if(set)
		{
			row = (64 - i - 1) / 8;
			column = i % 8;
			break;
		}	
	}
	return Coordinate(row, column);
}

int BitBoard::PieceCount( bitBoard_t pieceBitBoard )
{
	int retVal = 0;

	bitBoard_t stateCopy = pieceBitBoard;
	bitBoard_t set = 0;

	for(int i = 0; i < 64; i++)
	{
		set = stateCopy & 1;
		stateCopy >>= 1;

		if(set)
			retVal++;
	}
	return retVal;
}

BitBoard* BitBoard::Generate( GameState* gameState )
{
	if(!gameState)
		return NULL;

	BitBoard* newBitBoard = new BitBoard();

	const char* boardString = gameState->board.c_str();
	
	//Begin filling bitboard
	for(int i = 64; i >= 0; i--)
	{
		switch(boardString[i])
		{
		case 'P':
			newBitBoard->whitePawns += 1;
			break;
		case 'R':
			newBitBoard->whiteRooks += 1;
			break;
		case 'B':
			newBitBoard->whiteBishops += 1;
			break;

		case 'p':
			newBitBoard->blackPawns += 1;
			break;
		case 'r':
			newBitBoard->blackRooks += 1;
			break;
		case 'b':
			newBitBoard->blackBishops += 1;
			break;
		}

		if(i > 0)
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

	newBitBoard->CalculateRelativeBitBoards();
	return newBitBoard;
}

void BitBoard::CalculateRelativeBitBoards()
{
	//Bitwise OR operator FTW.
	this->whitePieces = this->whitePawns | this->whiteRooks | this->whiteBishops;
	this->blackPieces = this->blackPawns | this->blackRooks | this->blackBishops;

	this->fullBoard = this->whitePieces | this->blackPieces;

	this->emptySpaces = UNIVERSE ^ this->fullBoard;
}

vector<bitBoard_t>* BitBoard::GetSpecificPieceList( bitBoard_t pieceBitBoard )
{
	vector<bitBoard_t>* returnList = new vector<bitBoard_t>();

	bitBoard_t stateCopy = pieceBitBoard;
	bitBoard_t set = 0;

	for(int i = 0; i < 64; i++)
	{
		set = stateCopy & 1;
		stateCopy >>= 1;

		if(set)
		{
			bitBoard_t foundPiece = 1;
			foundPiece <<= i;
			returnList->push_back(foundPiece);
		}

	}
	return returnList;
}

vector<bitBoard_t>* BitBoard::GetWhitePawns()
{
	return BitBoard::GetSpecificPieceList(this->whitePawns);
}

vector<bitBoard_t>* BitBoard::GetWhiteRooks()
{
	return BitBoard::GetSpecificPieceList(this->whiteRooks);
}

vector<bitBoard_t>* BitBoard::GetWhiteBishops()
{
	return BitBoard::GetSpecificPieceList(this->whiteBishops);
}

bitBoard_t BitBoard::SwapBitBoard( bitBoard_t bitBoard )
{
	bitBoard_t stateCopy = bitBoard;
	bitBoard_t retVal = 0;
	bitBoard_t set = 0;

	for(int i = 0; i < 64; i++)
	{
		set = stateCopy & 1;
		stateCopy >>= 1;

		if(set)
		{
			retVal += 1;
			
		}

		if(i < 63)
			retVal <<= 1;
	}

	return retVal;
}


BitBoard* BitBoard::Swap( BitBoard* bitBoard )
{
	if(!bitBoard)
		return NULL;

	BitBoard* swappedBitBoard = new BitBoard();

	swappedBitBoard->whitePawns = SwapBitBoard(bitBoard->blackPawns);
	swappedBitBoard->whiteRooks = SwapBitBoard(bitBoard->blackRooks);
	swappedBitBoard->whiteBishops = SwapBitBoard(bitBoard->blackBishops);

	swappedBitBoard->blackPawns = SwapBitBoard(bitBoard->whitePawns);
	swappedBitBoard->blackRooks = SwapBitBoard(bitBoard->whiteRooks);
	swappedBitBoard->blackBishops = SwapBitBoard(bitBoard->whiteBishops);

	swappedBitBoard->CalculateRelativeBitBoards();

	return swappedBitBoard;
}

bool BitBoard::IsFinalState()
{
	return BitBoard::PieceCount(this->whitePawns & BitBoard::EIGHTHCOLUMN);
}



