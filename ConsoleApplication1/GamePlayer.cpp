#include "stdafx.h"
#include "GamePlayer.h"

#include <iostream>
#include <sstream>

GamePlayer::GamePlayer()
{
}


GamePlayer::~GamePlayer()
{
}


// Returns the choice # (returns 0 if some other command was typed, or the choice was invalid)
// Handles other types of input for other commands (inventory, exit, etc...)
unsigned int GamePlayer::HandleInput(bool &bRunning) const
{
	unsigned int choiceInput = 0;
	string inputStr;

	cin.clear(); // clear whatever's in the buffer.
	getline(cin, inputStr);

	istringstream iss(inputStr); // Creates a string stream from the string
	string cmd;
	string param;

	iss >> cmd; // first word is the command;
	iss >> param; // second word (if exists) is the param... may be more than one
	if (cmd == "h" || cmd == "help" || cmd == "?")
	{
		DisplayHelp();
	}
	else if ((cmd == "exit"))
	{
		bRunning = false;
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


void GamePlayer::DisplayHelp() const
{
	// Must use spaces, not tabs, when aligning these strings!
	cout << " ---- HELP: ---- " << endl;
	cout << "? / help / h:          help" << endl;
	cout << "exit:                  exits game." << endl;
	cout << "get / pickup <item>    picks up item." << endl;
	cout << "drop <item>            drops item." << endl;
}


void GamePlayer::DisplayInventory() const
{
	// Must use spaces, not tabs, when aligning these strings!
	cout << " ---- INVENTORY: ---- " << endl;
	// TODO: display user's inventory
	cout << endl;
}