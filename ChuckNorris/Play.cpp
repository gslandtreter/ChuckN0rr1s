#include "Play.h"


Play::Play(void)
{
	playBitBoard = NULL;
	origin = Coordinate(0,0);
	destination = Coordinate(0,0);
}


Play::~Play(void)
{
}

void Play::SwapPlayCoordinates()
{
	this->origin.Swap();
	this->destination.Swap();
}
