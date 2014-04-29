#pragma once

#include "json.h"
#include <string>
#include "GameState.h"

using namespace std;

class ChuckJson
{
public:
	ChuckJson(void);
	~ChuckJson(void);

	static string GetNameJson( string name );
	static GameState* ParseGameState(string gameStateJson);

};

