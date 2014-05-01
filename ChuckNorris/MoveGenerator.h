#pragma once

#include "BitBoard.h"
#include "GameState.h"
#include <vector>
#include "Play.h"

using namespace std;

class MoveGenerator
{
public:

	static void GeneratePawnMovements(BitBoard* currentState, bitBoard_t pawn, vector<Play*>* resultList);
	static void GenerateRookMovements(BitBoard* currentState, bitBoard_t rook, vector<Play*>* resultList);

	static void GenerateAllPawnMovements(BitBoard* currentState, vector<Play*>* resultList);
	static void GenerateAllRookMovements(BitBoard* currentState, vector<Play*>* resultList);

	static vector<Play*>* GenerateAllMovements(BitBoard* currentState);

	MoveGenerator(void);
	~MoveGenerator(void);
};

