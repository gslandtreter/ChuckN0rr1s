#pragma once

#include "json.h"
#include <string>

using namespace std;

class ChuckJason
{
public:
	ChuckJason(void);
	~ChuckJason(void);

	static string GetNameJson( string name );
};

