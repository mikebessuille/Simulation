#include "stdafx.h"
#include "GameGraph.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <pugixml.hpp>

GameGraph::GameGraph()
{
	bool bRet = parseXML("game.xml");
	if (bRet == false)
	{
		cout << "*** ERROR: GAME NOT LOADED ***" << endl;
	}
	else
	{
		cout << "Game Loaded." << endl;
	}
}


GameGraph::~GameGraph()
{
}


void GameGraph::play()
{
	// Always start at index 0?  Go until current > graph.size()?
	int current = 0;
	while (( current >= 0 ) && ( current < graph.size()))
	{
		current = graph[current].takeChoice();
	}

	if (current != -1 && current >= graph.size())
	{
		cout << " *** ERROR:  node not found: " << current << endl;
	}
}

struct TempChoice
{
	int OriginIndex;
	string newNodeName;
	int newNodeIndex;
	string prompt;
};

bool GameGraph::parseXML(string file)
{
	pugi::xml_document doc;
	const char *cstr = file.c_str();
	doc.load_file(cstr);
	if (doc.empty())
	{
		return(false);
	}
	
	// FIRST PASS:  Build up the Node list (graph), and a separate list of choices
	vector<TempChoice> temp_choices; 

	pugi::xml_node menus = doc.child("menus");
	int index = 0;
	for (pugi::xml_node menu = menus.child("menu"); menu; menu = menu.next_sibling("menu"))
	{
		const pugi::char_t* name = menu.attribute("name").value();
		const pugi::char_t* prompt = menu.child_value("prompt");
		graph.push_back(GameNode(name, prompt));

		// For now, store the choices in a separate structure called temp_choices.  They aren't part of graph yet.
		pugi::xml_node choices = menu.child("choices");
		for (pugi::xml_node choice = choices.child("choice"); choice; choice = choice.next_sibling("choice"))
		{
			string choice_text = choice.first_child().value();
			string choice_link = choice.attribute("link").value();
			temp_choices.push_back({ index, choice_link, -1, choice_text }); // For now, it's newNodeIndex is unknown, so -1
		}
		index++;
	}

	// SECOND PASS:  convert all the string names into indices, now that we have all the node names.
	unsigned int nodeIndex = 0;
	for (auto & node : graph)
	{
		for(auto & choice : temp_choices)
		{
			if (node == choice.newNodeName)
			{
				if (choice.OriginIndex == nodeIndex)
				{
					// This will lead to a neverending loop...  choice goes to the current location
					cout << "*** WARNING:  Index points to current node. " << choice.OriginIndex << " Title: " << choice.newNodeName << endl;
				}
				else
				{
					choice.newNodeIndex = nodeIndex;
				}
			}
		}
		nodeIndex++;
	}


	// THIRD PASS:  Add the choices to the appropriate nodes in the nodelist (graph), now that we have all the Node indices.
	pair<int, string > newChoice;
	const int numNodes = graph.size();
	for (auto & choice : temp_choices)
	{
		if (choice.newNodeIndex >= 0 && choice.newNodeIndex < numNodes )
		{
			newChoice.first = choice.newNodeIndex;
			newChoice.second = choice.prompt;
			graph[choice.OriginIndex].AddChoice(newChoice);
		}
		else
		{
			// None of them should be -1...
			cout << " *** ERROR:   Node not found: " << choice.newNodeName << endl;
			// for debug purposes:
			newChoice.first = choice.OriginIndex; // so that it just stays in the same place for now.
			newChoice.second = "MISSING: " + choice.prompt;
			graph[choice.OriginIndex].AddChoice(newChoice);
		}
	}

	return(true);
}



// TODO:
// Different things than choices?  Other attributes?  HP for the character?  Experience?  Levels?  Items that can be held / dropped ?
// States for various nodes? (Door is open / closed...)