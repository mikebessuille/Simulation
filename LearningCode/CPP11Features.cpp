#include "CPP11Features.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>
#include <cassert>

using namespace std;

CPP11Features::CPP11Features()
{
}


CPP11Features::~CPP11Features()
{
}

void CPP11Features::run()
{
	UsingAuto();
	UsingInitialization();
	UsingAlias();
	UsingNullptr();
	UsingPointerTypes();
}

void CPP11Features::UsingAuto()
{

}

void CPP11Features::UsingInitialization()
{
	// simple types
	int x(3);
	int y = 4;
	int z{ 5 };

	// objects
	// list initialization
	// diff between () and {} and int x = 3;
}

void CPP11Features::UsingAlias()
{
	// OLD:
	// typedef unordered_map<string, string> StringMap;
	
	// NEW:
	using StringMap = unordered_map<string, string>;
	StringMap teamList {	{ "Ottawa", "Sens" },
							{ "Toronto", "Leafs" } };
	unsigned int numTeams = static_cast<unsigned int>(teamList.size());
	assert( numTeams == 2);
	cout << "Num Teams:" << numTeams << endl;
	
}

void CPP11Features::UsingNullptr()
{

}

void CPP11Features::UsingEnums()
{

}

void CPP11Features::UsingPointerTypes()
{

}