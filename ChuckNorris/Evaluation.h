#pragma once

#include "Play.h"
#include "PlayTree.h"
#include <vector>;


class Evaluation
{
public:
	Evaluation(void);
	~Evaluation(void);

	static int EvaluateScore(Play* play);
	static void EvaluatePlayList(vector<Play*>* playList);
	static void EvaluateTreeChildren(PlayTree* playTree);

	static int MiniMax(PlayTree* playTree, bool max);
};

