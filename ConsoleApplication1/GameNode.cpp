#include "stdafx.h"
#include "GameNode.h"

#include <iostream>



GameNode::GameNode(	const string& title, const string& description,
					const vector<pair<int, string> > &choices ) : // default value is an empty vector
	_title( title ),
	_desc( description ),
	_choices(choices)
{
}

GameNode::~GameNode()
{
}


bool GameNode::operator==(const std::string &name) const
{
	return( _title == name );
}


void GameNode::AddChoice( const pair<int, string> &choice )
{
	_choices.push_back(choice);
}


const int GameNode::takeChoice() const
{
	if (_choices.size() == 0)
	{
		cout << _title << endl; // For debug purposes
		cout << _desc << endl;
		cout << " *** THE END *** " << endl;
		return(-1);
	}

	unsigned int choice;
	int i;
	do
	{
		cout << _title << endl; // For debug purposes
		cout << _desc << endl;
		i = 1;
		for (auto ch : _choices)
		{
			std::cout << i++ << ": " << ch.second << "\n";
		}
		cin >> choice;
		choice--;
	} while (choice >= _choices.size());
	// Return the index of the next node.
	return _choices[choice].first;
}