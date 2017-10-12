#pragma once

#include <string>
#include <vector>
#include <list>
#include <memory>
#include "GamePlayer.h"

using namespace std;

class GameNode
{
public:
	GameNode(	const string& title, const string& description,
				const vector<pair<int, string>>& = vector<pair<int, string>>{}); // default value is an empty vector
	~GameNode();
	void AddChoice( const pair<int, string> &choice );
	const int takeChoice( GamePlayer &player ) const;
	bool operator==(const string&) const;

private:
	void Display() const;
	

private:
	string _title;
	string _desc;
	vector<pair<int, string>> _choices; // int = destination node;  string = prompt
};

