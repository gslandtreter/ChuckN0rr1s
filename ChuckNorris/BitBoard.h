#pragma once


#include <stdint.h>
#include <stdio.h>
#include "GameState.h"
#include <vector>

typedef uint64_t bitBoard_t;
using namespace std;

class BitBoard
{
public:

	static const bitBoard_t EMPTY = 0;
	static const bitBoard_t UNIVERSE = 0xffffffffffffffffULL;
	static const bitBoard_t FIRST = 0x8000000000000000ULL;

	static const bitBoard_t FIRSTCOLUMN =   0xFF00000000000000ULL;
	static const bitBoard_t SECONDCOLUMN =  0x00FF000000000000ULL;
	static const bitBoard_t THIRDCOLUMN =   0x0000FF0000000000ULL;
	static const bitBoard_t FOURTHCOLUMN =  0x00000FF000000000ULL;
	static const bitBoard_t FIFTHCOLUMN =   0x00000000FF000000ULL;
	static const bitBoard_t SIXTHCOLUMN =   0x0000000000FF0000ULL;
	static const bitBoard_t SEVENTHCOLUMN = 0x000000000000FF00ULL;
	static const bitBoard_t EIGHTHCOLUMN =  0x00000000000000FFULL;

	static const bitBoard_t notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
	static const bitBoard_t notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

	bitBoard_t whitePawns;
	bitBoard_t whiteRooks;
	bitBoard_t whiteBishops;
	bitBoard_t whitePieces;

	bitBoard_t blackPawns;
	bitBoard_t blackRooks;
	bitBoard_t blackBishops;
	bitBoard_t blackPieces;

	bitBoard_t fullBoard;
	bitBoard_t emptySpaces;

	BitBoard(void);
	~BitBoard(void);

	static bitBoard_t GoNorth (bitBoard_t currentBitBoard);
	static bitBoard_t GoSouth (bitBoard_t currentBitBoard);
	static bitBoard_t GoEast (bitBoard_t currentBitBoard);
	static bitBoard_t GoWest (bitBoard_t currentBitBoard);
	static bitBoard_t GoSouthEast (bitBoard_t currentBitBoard);
	static bitBoard_t GoSouthWest (bitBoard_t currentBitBoard);
	static bitBoard_t GoNorthEast (bitBoard_t currentBitBoard);
	static bitBoard_t GoNorthWest (bitBoard_t currentBitBoard);

	static void PrintBitBoard(bitBoard_t bitBoard);
	static bitBoard_t SwapBitBoard(bitBoard_t bitBoard);
	static BitBoard* Generate(GameState* gameState);
	static Coordinate GetPieceCoordinate(bitBoard_t bitBoard);
	static int PieceCount(bitBoard_t bitBoard);
	static BitBoard* Swap(BitBoard* bitBoard);

	void CalculateRelativeBitBoards();

	static vector<bitBoard_t>* GetSpecificPieceList(bitBoard_t pieceBitBoard);

	vector<bitBoard_t>* GetWhitePawns();
	vector<bitBoard_t>* GetWhiteRooks();
	vector<bitBoard_t>* GetWhiteBishops();
	
};

