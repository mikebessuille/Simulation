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


const int GameNode::takeChoice() const
{
	if (_choices.size() == 0)
	{
		Display();
		cout << " *** THE END *** " << endl;
		return(-1);
	}

	unsigned int choice;
	do
	{
		Display();
		choice = HandleInput();
		choice--;
	} while (choice >= _choices.size());
	// Return the index of the next node.
	return _choices[choice].first;
}


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


// Returns the choice # (returns 0 if some other command was typed, or the choice was invalid)
// Handles other types of input for other commands (inventory, exit, etc...)
unsigned int GameNode::HandleInput() const
{
	unsigned int choiceInput = 0;
	string inputStr;

	cin.clear(); // clear whatever's in the buffer.
	getline( cin, inputStr );

	istringstream iss(inputStr); // Creates a string stream from the string
	string cmd;
	string param;
	
	iss >> cmd; // first word is the command;
	iss >> param; // second word (if exists) is the param... may be more than one
	if (cmd == "h" || cmd == "help" || cmd == "?")
	{
		DisplayHelp();
	}
	else if ((cmd == "exit") || (cmd == "x"))
	{
		// TODO: quit this program
	}
	else if (cmd == "inventory" || cmd == "i")
	{
		DisplayInventory();
	}
	else
	{
		// No command found.  Could be a choice.
		istringstream iss2(inputStr); // new string stream just for converting to an unsigned int
		iss2 >> choiceInput;
	}

	return(choiceInput);
}

void GameNode::DisplayHelp() const
{
	// Must use spaces, not tabs, when aligning these strings!
	cout << " ---- HELP: ---- "  << endl;
	cout << "? / help / h:          help" << endl;
	cout << "exit / x:              exits game." << endl;
	cout << "get / pickup <item>    picks up item." << endl;
	cout << "drop <item>            drops item." << endl;
}

void GameNode::DisplayInventory() const
{
	// Must use spaces, not tabs, when aligning these strings!
	cout << " ---- INVENTORY: ---- " << endl;
	// TODO: display user's inventory
	cout << endl;
}
