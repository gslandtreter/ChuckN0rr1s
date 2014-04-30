#pragma once

#include "BitBoard.h"
#include "GameState.h"
#include <vector>

using namespace std;

class MoveGenerator
{
public:

	static vector<bitBoard_t>* GetWhitePawns(BitBoard* currentState);
	static vector<BitBoard*>* GeneratePawnMovements(BitBoard* currentState, bitBoard_t pawn);

	MoveGenerator(void);
	~MoveGenerator(void);
};

