#pragma once

#include <vector>

using namespace std;

class Play;

class PlayTree
{
public:
	PlayTree(void);
	~PlayTree(void);

	Play* currentPlay;
	vector<PlayTree*>* possiblePlays;
	int score;
};

