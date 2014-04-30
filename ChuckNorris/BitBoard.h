#pragma once


#include <stdint.h>
#include <stdio.h>
#include "GameState.h"


typedef uint64_t bitBoard_t;


class BitBoard
{
public:

	static const bitBoard_t EMPTY = 0;
	static const bitBoard_t UNIVERSE = 0xffffffffffffffffULL;

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
	static bitBoard_t GoNorthEast (bitBoard_t currentBitBoard);
	static bitBoard_t GoNorthWest (bitBoard_t currentBitBoard);

	static void PrintBitBoard(bitBoard_t bitBoard);
	static BitBoard* Generate(GameState* gameState);
	static Coordinate GetPieceCoordinate(bitBoard_t bitBoard);

	void CalculateRelativeBitBoards();
	
};

