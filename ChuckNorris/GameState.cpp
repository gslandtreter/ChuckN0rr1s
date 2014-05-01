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

void Coordinate::Swap()
{
	this->x = 7 - this->x;
	this->y = 7 - this->y;
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

void GameState::PrintBoard()
{
	const char* boardChar = this->board.c_str();

	for(int i = 0; i < 64; i ++)
	{
		if((i % 8) == 0)
			printf("\n");
		printf("%c", boardChar[i]);
	}
}

void GameState::SwapBoard()
{
	this->board = string ( this->board.rbegin(), this->board.rend() );

	for(int i = 0; i < this->board.size(); i++)
	{
		switch(this->board[i])
			{
			case 'P':
				this->board[i] = 'p';
				break;
			case 'R':
				this->board[i] = 'r';
				break;
			case 'B':
				this->board[i] = 'b';
				break;

			case 'p':
				this->board[i] = 'P';
				break;
			case 'r':
				this->board[i] = 'R';
				break;
			case 'b':
				this->board[i] = 'B';
				break;
			}
	}
}
