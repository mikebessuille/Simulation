#pragma once

#include "UnitMgr.h"

class Player
{
public:
	Player(std::string n);
	~Player();
	mutex & GetMutex() { return UM.GetMutex(); };
	void Update(GameState &gs, const unsigned long nTick) { UM.Update(gs, nTick); };

public:
	UnitMgr UM;
	std::string Name;
};

