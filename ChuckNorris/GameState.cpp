#include "GameState.h"


Coordinate::Coordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Coordinate::PrintCoordinate()
{
	printf("(%d %d)",x,y);
}

Coordinate::Coordinate( void )
{

}
Coordinate::~Coordinate( void )
{

}

Coordinate* Coordinate::Parse(string strToParse)
{
	if(strToParse == "null")
		return NULL;

	Coordinate* newCoord = new Coordinate();
	int x = 0, y = 0;

	//TODO: Como eh coord, tem q fazer o parsing dessa merda.

	return NULL;

}

//////////////////////////////////////////////////
GameState::GameState(void)
{
	
}


GameState::~GameState(void)
{
}

void GameState::Print()
{
	printf("-----\nGAMESTATE:\n");

	printf("Board:             %s\n", this->board.c_str());
	if(this->enpassant)
		{printf("Enpassant:         "); this->enpassant->PrintCoordinate(); printf("\n");}
	printf("Who Moves:         %d\n", this->whoMoves);
	printf("Bad Move:          %s\n", this->badMove ? "true" : "false");
	printf("White Infractions: %d\n", this->whiteInfractions);
	printf("Black Infractions: %d\n", this->blackInfractions);
	printf("Winner:            %d\n", this->winner);
	printf("50 Moves:          %s\n", this->fiftyMoves ? "true" : "false");
	printf("Draw:              %s\n", this->draw ? "true" : "false");

	return;
}
