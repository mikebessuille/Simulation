#pragma once

#include <string>
#include <list>

using namespace std;
//using UnitType = const unsigned int;
enum class UnitType : unsigned int { TANK, FIGHTER, TRANSPORT, MOBILE_AA };

struct UnitTypeFull
{
	std::string name;
	UnitType type;
};

// TODO: Turn this into a map, instead of using the struct?
static list<UnitTypeFull> supportedUnits = {
	{ "Tank", UnitType::TANK },
	{ "Mobile AA", UnitType::MOBILE_AA },
	{ "Transport Plane", UnitType::TRANSPORT },
	{ "Fighter", UnitType::FIGHTER },
};


// TODO: How to make an extensible list of constant ID's and their string names, which is easy to populate in a static list?
