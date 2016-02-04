#pragma once

#include "UnitBase.h"
#include <vector>
#include <iostream>


// using namespace std;

class UnitMgr
{
public:
	UnitMgr();
	~UnitMgr();
	

private:
	std::vector<UnitBase*> unitList;
};

