#pragma once

#include "json.h"
#include <string>
#include "GameState.h"
#include "Play.h"

using namespace std;

class ChuckJson
{
public:
	ChuckJson(void);
	~ChuckJson(void);

	static string GetNameJson( string name );
	static GameState* ParseGameState(string gameStateJson);
	static string GetPlayJson( Play* play );

};

