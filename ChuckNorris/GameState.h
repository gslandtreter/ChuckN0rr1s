#pragma once

#include <string>
#include <stdio.h>
using namespace std;

class Coordinate
{
public:
	int x;
	int y;

	Coordinate(void);
	~Coordinate(void);

	Coordinate(int x, int y);
	void PrintCoordinate();

	static Coordinate* Parse(string strToParse);

};

class GameState
{
public:

	string board;
	Coordinate* enpassant;
	int whoMoves;
	bool badMove;
	int whiteInfractions;
	int blackInfractions;
	int winner;
	bool fiftyMoves;
	bool draw;

	GameState(void);
	~GameState(void);

	void Print();
};

