#pragma once

#include <string>
#include <vector>
#include <list>
#include <memory>

using namespace std;

class GamePlayer
{
public:
	GamePlayer();
	~GamePlayer();
	unsigned int HandleInput(bool &) const;

private:
	void DisplayHelp() const; // should be moved to other class...
	void DisplayInventory() const; // move to other class

private:
	// TODO:  Inventory
};

