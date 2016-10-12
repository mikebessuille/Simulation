#pragma once

#include <string>
#include <list>

using namespace std;
using UnitType = const unsigned int;

struct UnitTypeFull
{
	std::string name;
	UnitType type;
};

static list<UnitTypeFull> supportedUnits = {
	{ "Tank", 0 },
	{ "Mobile AA", 1 },
	{ "Transport Plane", 2 },
	{ "Fighter", 3 },
};


// TODO: remove this... just testing enums
enum class UnitType2 { TANK, FIGHTER, TRANSPORT };

UnitType2 myType = UnitType2::FIGHTER;

// TODO: How to make an extensible list of constant ID's and their string names, which is easy to populate in a static list?
