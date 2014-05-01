#include "MoveGenerator.h"


MoveGenerator::MoveGenerator(void)
{
}


MoveGenerator::~MoveGenerator(void)
{
}


vector<Play*>* MoveGenerator::GenerateAllMovements( BitBoard* currentState )
{
	vector<Play*>* generatedMovementList = new vector<Play*>();

	MoveGenerator::GenerateAllRookMovements(currentState, generatedMovementList);
	MoveGenerator::GenerateAllPawnMovements(currentState, generatedMovementList);
	
	return generatedMovementList;
}



void MoveGenerator::GeneratePawnMovements( BitBoard* currentState, bitBoard_t pawn, vector<Play*>* resultList )
{
	if(!currentState || !pawn)
		return;

	bitBoard_t pawnForward = BitBoard::GoNorth(pawn) & currentState->emptySpaces;
	bitBoard_t pawnNorthEast = BitBoard::GoNorthEast(pawn) & currentState->blackPieces;
	bitBoard_t pawnNorthWest = BitBoard::GoNorthWest(pawn) & currentState->blackPieces;

	Coordinate pawnCoordinate = BitBoard::GetPieceCoordinate(pawn);

	//TODO: Double forward when first move.
	if(pawnForward) //No one is obstructing pawn! Go Forward!!!
	{
		Play* newPlay = new Play();
		BitBoard* newState = new BitBoard();

		newState->whiteRooks = currentState->whiteRooks;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whitePawns = (currentState->whitePawns ^ pawn) | pawnForward;

		newState->blackBishops = currentState->blackBishops;
		newState->blackPawns = currentState->blackPawns;
		newState->blackRooks = currentState->blackRooks;

		newState->CalculateRelativeBitBoards();

		newPlay->origin = pawnCoordinate;
		newPlay->destination = BitBoard::GetPieceCoordinate(pawnForward);
		newPlay->playBitBoard = newState;

		resultList->push_back(newPlay);
	}

	if(pawnNorthEast) //Theres a black piece northeast, go get it!
	{
		Play* newPlay = new Play();
		BitBoard* newState = new BitBoard();

		newState->whiteRooks = currentState->whiteRooks;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whitePawns = (currentState->whitePawns ^ pawn) | pawnNorthEast;

		newState->blackBishops = currentState->blackBishops ^ pawnNorthEast;
		newState->blackPawns = currentState->blackPawns ^ pawnNorthEast;
		newState->blackRooks = currentState->blackRooks ^ pawnNorthEast;

		newState->CalculateRelativeBitBoards();

		newPlay->origin = pawnCoordinate;
		newPlay->destination = BitBoard::GetPieceCoordinate(pawnNorthEast);
		newPlay->playBitBoard = newState;

		resultList->push_back(newPlay);
	}

	if(pawnNorthWest) //Theres a black piece northwest, go get it!
	{
		Play* newPlay = new Play();
		BitBoard* newState = new BitBoard();

		newState->whiteRooks = currentState->whiteRooks;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whitePawns = (currentState->whitePawns ^ pawn) | pawnNorthWest;

		newState->blackBishops = currentState->blackBishops ^ pawnNorthWest;
		newState->blackPawns = currentState->blackPawns ^ pawnNorthWest;
		newState->blackRooks = currentState->blackRooks ^ pawnNorthWest;

		newState->CalculateRelativeBitBoards();

		newPlay->origin = pawnCoordinate;
		newPlay->destination = BitBoard::GetPieceCoordinate(pawnNorthWest);
		newPlay->playBitBoard = newState;

		resultList->push_back(newPlay);
	}

}

void MoveGenerator::GenerateRookMovements( BitBoard* currentState, bitBoard_t rook, vector<Play*>* resultList )
{
	if(!currentState || !rook)
		return;

	bitBoard_t emptyOrBlack = currentState->emptySpaces | currentState->blackPieces;

	bitBoard_t rookForward = BitBoard::GoNorth(rook) & emptyOrBlack;

	Coordinate rookCoordinate = BitBoard::GetPieceCoordinate(rook);

	while(rookForward)
	{
		Play* newPlay = new Play();
		BitBoard* newState = new BitBoard();

		newState->whitePawns = currentState->whitePawns;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whiteRooks = (currentState->whiteRooks ^ rook) | rookForward;

		newState->blackBishops = currentState->blackBishops ^ rookForward;
		newState->blackPawns = currentState->blackPawns ^ rookForward;
		newState->blackRooks = currentState->blackRooks ^ rookForward;

		newState->CalculateRelativeBitBoards();

		newPlay->origin = rookCoordinate;
		newPlay->destination = BitBoard::GetPieceCoordinate(rookForward);
		newPlay->playBitBoard = newState;

		resultList->push_back(newPlay);

		if(rookForward & currentState->blackPieces) //Se encontrou uma peça preta no caminho, termina o loop
			break;

		rookForward = BitBoard::GoNorth(rookForward) & emptyOrBlack;
	}

	
	bitBoard_t rookEast = BitBoard::GoEast(rook) & emptyOrBlack;

	while(rookEast)
	{
		Play* newPlay = new Play();
		BitBoard* newState = new BitBoard();

		newState->whitePawns = currentState->whitePawns;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whiteRooks = (currentState->whiteRooks ^ rook) | rookEast;

		newState->blackBishops = currentState->blackBishops ^ rookEast;
		newState->blackPawns = currentState->blackPawns ^ rookEast;
		newState->blackRooks = currentState->blackRooks ^ rookEast;

		newState->CalculateRelativeBitBoards();

		newPlay->origin = rookCoordinate;
		newPlay->destination = BitBoard::GetPieceCoordinate(rookEast);
		newPlay->playBitBoard = newState;

		resultList->push_back(newPlay);

		if(rookEast & currentState->blackPieces) //Se encontrou uma peça preta no caminho, termina o loop
			break;

		rookEast = BitBoard::GoEast(rookEast) & emptyOrBlack;

	}

	bitBoard_t rookWest = BitBoard::GoWest(rook) & emptyOrBlack;

	while(rookWest)
	{
		Play* newPlay = new Play();
		BitBoard* newState = new BitBoard();

		newState->whitePawns = currentState->whitePawns;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whiteRooks = (currentState->whiteRooks ^ rook) | rookWest;

		newState->blackBishops = currentState->blackBishops ^ rookWest;
		newState->blackPawns = currentState->blackPawns ^ rookWest;
		newState->blackRooks = currentState->blackRooks ^ rookWest;

		newState->CalculateRelativeBitBoards();

		newPlay->origin = rookCoordinate;
		newPlay->destination = BitBoard::GetPieceCoordinate(rookWest);
		newPlay->playBitBoard = newState;

		resultList->push_back(newPlay);

		if(rookWest & currentState->blackPieces) //Se encontrou uma peça preta no caminho, termina o loop
			break;

		rookWest = BitBoard::GoWest(rookWest) & emptyOrBlack;
	}
	
	bitBoard_t rookSouth = BitBoard::GoSouth(rook) & emptyOrBlack;

	while(rookSouth)
	{
		Play* newPlay = new Play();
		BitBoard* newState = new BitBoard();

		newState->whitePawns = currentState->whitePawns;
		newState->whiteBishops = currentState->whiteBishops;
		newState->whiteRooks = (currentState->whiteRooks ^ rook) | rookSouth;

		newState->blackBishops = currentState->blackBishops ^ rookSouth;
		newState->blackPawns = currentState->blackPawns ^ rookSouth;
		newState->blackRooks = currentState->blackRooks ^ rookSouth;

		newState->CalculateRelativeBitBoards();

		newPlay->origin = rookCoordinate;
		newPlay->destination = BitBoard::GetPieceCoordinate(rookSouth);
		newPlay->playBitBoard = newState;

		resultList->push_back(newPlay);

		if(rookSouth & currentState->blackPieces) //Se encontrou uma peça preta no caminho, termina o loop
			break;

		rookSouth = BitBoard::GoSouth(rookSouth) & emptyOrBlack;
	}
}


void MoveGenerator::GenerateAllPawnMovements( BitBoard* currentState, vector<Play*>* resultList )
{
	vector<bitBoard_t>* gotWhitePawns = currentState->GetWhitePawns();

	for(int i = 0; i < gotWhitePawns->size(); i++)
	{
		MoveGenerator::GeneratePawnMovements(currentState, (*gotWhitePawns)[i], resultList);
	}
}

void MoveGenerator::GenerateAllRookMovements( BitBoard* currentState, vector<Play*>* resultList )
{
	vector<bitBoard_t>* gotWhiteRooks = currentState->GetWhiteRooks();

	for(int i = 0; i < gotWhiteRooks->size(); i++)
	{
		MoveGenerator::GenerateRookMovements(currentState, (*gotWhiteRooks)[i], resultList);
	}
}




