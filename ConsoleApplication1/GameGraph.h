#pragma once

#include <string>
#include <vector>
#include <list>
#include "GameNode.h"

using namespace std;


class GameGraph
{
public:
	GameGraph();
	~GameGraph();
	void play();

private:
	bool parseXML( string file );

private:
	vector<GameNode> graph;
};

