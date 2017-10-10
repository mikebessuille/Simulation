#pragma once

#include "MenuNode.h"

class GameFile
{
public:
	GameFile();
	~GameFile();

	void play();
	std::vector<MenuNode> parseXML(std::string file);

};
