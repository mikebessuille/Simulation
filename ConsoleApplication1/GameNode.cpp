#include "stdafx.h"
#include "GameNode.h"

#include <iostream>
#include <sstream>


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


const int GameNode::takeChoice( GamePlayer &player ) const
{
	if (_choices.size() == 0)
	{
		Display();
		cout << " *** THE END *** " << endl;
		return(-1);
	}

	unsigned int choice;
	bool bRunning = true;
	do
	{
		Display();
		choice = player.HandleInput( bRunning );
		choice--;
	} while (choice >= _choices.size() && bRunning );

	if (!bRunning)
	{
		// program was aborted with "exit" command
		return(-1);
	}

	// Return the index of the next node.
	return _choices[choice].first;
}


// Displays this node
void GameNode::Display() const
{
	cout << "------------------------------------------" << endl;
	cout << _title << endl; // For debug purposes
	cout << _desc << endl;
	if (_choices.size() > 0)
	{
		int i = 1;
		for (auto ch : _choices)
		{
			std::cout << i++ << ": " << ch.second << endl;
		}
	}
}

