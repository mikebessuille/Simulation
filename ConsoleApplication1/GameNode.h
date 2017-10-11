#pragma once

#include <string>
#include <vector>
#include <list>

using namespace std;

class GameNode
{
public:
	GameNode(	const string& title, const string& description,
				const vector<pair<int, string>>& = vector<pair<int, string>>{}); // default value is an empty vector
	~GameNode();
	void AddChoice( const pair<int, string> &choice );
	const int takeChoice() const;
	bool operator==(const string&) const;

private:
	void Display() const;
	unsigned int HandleInput( bool &) const;

	void DisplayHelp() const; // should be moved to other class...
	void DisplayInventory() const; // move to other class

private:
	string _title;
	string _desc;
	vector<pair<int, string>> _choices; // int = destination node;  string = prompt
};

