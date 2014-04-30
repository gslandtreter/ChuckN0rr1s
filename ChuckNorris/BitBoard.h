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

	static void PrintBitBoard(bitBoard_t bitBoard);
	static BitBoard* Generate(GameState* gameState);

};

