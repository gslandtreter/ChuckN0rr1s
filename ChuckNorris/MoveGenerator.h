#pragma once

#include "BitBoard.h"
#include "GameState.h"
#include <vector>
#include "Play.h"

using namespace std;

class MoveGenerator
{
public:

	static vector<bitBoard_t>* GetWhitePawns(BitBoard* currentState);
	static vector<Play*>* GeneratePawnMovements(BitBoard* currentState, bitBoard_t pawn);

	MoveGenerator(void);
	~MoveGenerator(void);
};

