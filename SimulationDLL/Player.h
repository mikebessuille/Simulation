#pragma once

#include "UnitMgr.h"

class Player
{
public:
	Player(std::string n);
	~Player();

public:
	UnitMgr UM;
	std::string Name;
};

