#include "MoveGenerator.h"

MoveGenerator::MoveGenerator(void)
{
}


MoveGenerator::~MoveGenerator(void)
{
}

vector<bitBoard_t>* MoveGenerator::GetWhitePawns( BitBoard* currentState )
{
	if(!currentState)
		return NULL;

	vector<bitBoard_t>* returnList = new vector<bitBoard_t>();

	bitBoard_t stateCopy = currentState->whitePawns;
	bitBoard_t set = 0;

	for(int i = 0; i < 64; i++)
	{
		set = stateCopy & 1;
		stateCopy >>= 1;

		if(set)
		{
			bitBoard_t foundPawn = 1;
			foundPawn <<= i;
			returnList->push_back(foundPawn);
		}
		
	}

	return returnList;
}

vector<BitBoard*>* MoveGenerator::GeneratePawnMovements( BitBoard* currentState, bitBoard_t pawn )
{
	if(!currentState || !pawn)
		return NULL;

	vector<BitBoard*>* returnList = new vector<BitBoard*>();

	bitBoard_t pawnForward = BitBoard::GoNorth(pawn) & currentState->emptySpaces;
	bitBoard_t pawnNorthEast = BitBoard::GoNorthEast(pawn) & currentState->blackPieces;
	bitBoard_t pawnNorthWest = BitBoard::GoNorthWest(pawn) & currentState->blackPieces;

	//TODO: Double forward when first move.
	if(pawnForward) //No one is obstructing pawn! Go Forward!!!
	{
		BitBoard* newState = new BitBoard();

		newState->whiteRooks = currentState->whiteRooks;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whitePawns = (currentState->whitePawns ^ pawn) | pawnForward;

		newState->blackBishops = currentState->blackBishops;
		newState->blackPawns = currentState->blackPawns;
		newState->blackRooks = currentState->blackRooks;

		newState->CalculateRelativeBitBoards();
		returnList->push_back(newState);
	}

	if(pawnNorthEast) //Theres a black piece northeast, go get it!
	{
		BitBoard* newState = new BitBoard();

		newState->whiteRooks = currentState->whiteRooks;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whitePawns = (currentState->whitePawns ^ pawn) | pawnNorthEast;

		newState->blackBishops = currentState->blackBishops ^ pawnNorthEast;
		newState->blackPawns = currentState->blackPawns ^ pawnNorthEast;
		newState->blackRooks = currentState->blackRooks ^ pawnNorthEast;

		newState->CalculateRelativeBitBoards();
		returnList->push_back(newState);
	}

	if(pawnNorthWest) //Theres a black piece northwest, go get it!
	{
		BitBoard* newState = new BitBoard();

		newState->whiteRooks = currentState->whiteRooks;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whitePawns = (currentState->whitePawns ^ pawn) | pawnNorthWest;

		newState->blackBishops = currentState->blackBishops ^ pawnNorthWest;
		newState->blackPawns = currentState->blackPawns ^ pawnNorthWest;
		newState->blackRooks = currentState->blackRooks ^ pawnNorthWest;

		newState->CalculateRelativeBitBoards();
		returnList->push_back(newState);
	}

	return returnList;
}
