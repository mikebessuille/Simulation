#pragma once

#include "Unit.h"
#include <vector>
#include <iostream>


// using namespace std;

class UnitMgr
{
public:
	UnitMgr();
	~UnitMgr();
	

private:
	std::vector<Unit*> unitList;
};

