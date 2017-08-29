// SimulationConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

// #include "SimDLL.h"
#include "Simulation.h"
#include "Game.h"
#include "Player.h"
#include "Tech1Factory.h"
#include "MoveComponentGroundBasic.h"
#include "UnitTypes.h"
#include "UnitMgr.h"
#include "OrderMove.h"
#include <memory>


using namespace std;


void CreateSomeUsers( Game &g )
{
	shared_ptr<Player> p(new Player("Mike"));
	g.playerList.push_back(p);
	p = make_shared<Player>("Bob");
	g.playerList.push_back(p);
	p = make_shared<Player>("Sally");
	g.playerList.push_back(p);

	cout << "Players:" << endl;
	for (auto pl : g.playerList)
	{
		cout << pl->Name << endl;
	}
	cout << endl;
}

void CreateSomeUnits(Game &g)
{
	Tech1Factory factory;

	// This next "No!..." comment was true when playerList was a list of <Player> instead of pointers to players
	// // auto pl = g.playerList.front(); // No!  This causes the first element of playerList to be copied into pl, because auto converts to "Player" instead of a reference to player
	// Player &pl = g.playerList.front();

	shared_ptr<Player> pl = g.playerList.front();
	shared_ptr<UnitBase> punit = factory.CreateUnit(UnitType::TANK, 10, 15);
	shared_ptr<Order> order = make_shared<OrderMove>(Point(300, 300));
	punit->AddOrder(order);
	pl->UM.AddUnit( punit );

	punit = factory.CreateUnit(UnitType::TANK, 30, 150);
	order = make_shared<OrderMove>(Point(20, 4));
	punit->AddOrder(order);
	order = make_shared<OrderMove>(Point(30, 100));
	punit->AddOrder(order);
	order = make_shared<OrderMove>(Point(400, 400));
	punit->AddOrder(order);
	pl->UM.AddUnit(punit);

	punit = factory.CreateUnit(UnitType::TANK, 170, 10);
	order = make_shared<OrderMove>(Point(4, 500));
	punit->AddOrder(order);
	order = make_shared<OrderMove>(Point(170, 100));
	punit->AddOrder(order);
	pl->UM.AddUnit(punit);

	cout << "Size of Unit list: " << pl->UM.NumUnits() << endl;
}


int main()
{
	std::cout << "Simulation Console Running.  Hit Enter to start Simulation..." << endl;
	// std::cin.ignore(); // Accepts user input.
	std::cin.get(); // gets any user input (requires user to hit enter as well)

	Game game;

	// TODO:  Move all this to a new Unit Test!!!
	CreateSomeUsers(game);
	CreateSomeUnits(game);

	game.InitializeGame();
	cout << "number of players: " << game.GetGameState().UMList.size() << endl;
	int nPlayerNum = 0;
	for (auto &pum : game.GetGameState().UMList )
	{
		cout << "Player [" << nPlayerNum << "] units: " << pum->NumUnits() << endl;
		nPlayerNum++;
	}


	cout << "Simulation Looping: Hit Enter to stop..." << endl;
	game.Start();
	cin.get(); // Waits for user input (enter).  Then stops the sim.
	game.Stop();


	// Test to see if we can restart the simulation after it's been stopped.
	cout << "Hit Enter to restart..." << endl;
	std::cin.get();
	game.Start();
	cin.get(); // Waits for user input (enter).  Then stops the sim.
	game.Stop();

    return 0;
}

