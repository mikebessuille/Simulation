#include "stdafx.h"
#include "GameFile.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <pugixml.hpp>

#include "MenuNode.h"

using namespace std;

//
// NOTE:  This has been superceded by GameGraph
//

GameFile::GameFile()
{
}


GameFile::~GameFile()
{
}

void GameFile::play()
{
	vector<MenuNode> game = parseXML("game.xml");

	auto menu = find(game.begin(), game.end(), "mainroad");
	while (menu != game.end())
	{
		menu = find(game.begin(), game.end(), menu->takeChoice());
	}

	cout << "*** ERROR: NO CHOICE FOUND ***" << endl;
}


vector<MenuNode> GameFile::parseXML(string file)
{
	vector<MenuNode> game;

	pugi::xml_document doc;
	const char *cstr = file.c_str();
	doc.load_file( cstr );

	pugi::xml_node menus = doc.child("menus");
	for (pugi::xml_node menu = menus.child("menu"); menu; menu = menu.next_sibling("menu"))
	{
		const pugi::char_t* name = menu.attribute("name").value();
		const pugi::char_t* prompt = menu.child_value("prompt");

		pugi::xml_node choices = menu.child("choices");
		vector<pair<string, string>> choices_vector;

		for (pugi::xml_node choice = choices.child("choice"); choice; choice = choice.next_sibling("choice"))
		{
			string choice_item = choice.first_child().value();
			string choice_link = choice.attribute("link").value();
			choices_vector.push_back({ choice_item, choice_link });
		}
		game.push_back( MenuNode( name, prompt, choices_vector ));
	}
	return game;
}



// TODO:
// Different things than choices?  Other attributes?  HP for the character?  Experience?  Levels?  Items that can be held / dropped ?
// States for various nodes? (Door is open / closed...)