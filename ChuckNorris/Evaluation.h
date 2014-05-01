#pragma once

#include "Play.h"
#include <vector>;

class Evaluation
{
public:
	Evaluation(void);
	~Evaluation(void);

	static int EvaluateScore(Play* play);
	static void EvaluatePlayList(vector<Play*>* playList);
};

