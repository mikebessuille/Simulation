#pragma once

#include <thread>
#include "Map.h"

using namespace std;

class Game; // forward declare

class Renderer
{
// Member Variables
private:
	bool bRunning;
	thread *pRenderThread;	// Keep this a pointer and instantiate in constructor, so that I avoid warnings
							// about exporting a class with STL class
	Game *pGame;			// parent!

// Public Methods
public:
	Renderer( Game *parent );
	~Renderer();
	void Start();
	void Stop();

// Private methods
private:
	void Loop();
	void RenderFrame();
	Map map;
};

