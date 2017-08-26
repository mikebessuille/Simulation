#include "Renderer.h"
#include "Game.h"
#include "UnitMgr.h"

#include <assert.h>
#include <mutex>



// TODO:  This class contains a lot of stuff (bRunning, thread management) that could be more easily handled by the Game class.
Renderer::Renderer( Game *parent ) :
	bRunning(false),
	pRenderThread(nullptr),
	pGame(parent)
{
	assert(pGame);
	map.Initialize();
}


Renderer::~Renderer()
{
	if (bRunning)
	{
		// some kind of error happened because the renderer object is being deleted while
		// the renderer is still running!
		cout << "Failed to Stop renderer before killing app\n";
	}
	if (pRenderThread)
	{
		if (pRenderThread->joinable())
			pRenderThread->join();  // main thread waits for SimThread to complete

		delete pRenderThread;
		pRenderThread = NULL;
	}
}


void Renderer::Start()
{
	//assert(bRunning == false);
	if (!bRunning)
	{
		cout << "Renderer Start\n";
		bRunning = true;
		map.Reset();
		assert(!pRenderThread);
		pRenderThread = new thread(&Renderer::Loop, this);
	}
}


void Renderer::Stop()
{
	bRunning = false;

	// Join the thread to the main thread so main waits for the thread to finish.
	// Setting the bRunning flag above should accomplish the same thing; the thread should immediately exit
	// (after it finishes processing the current tick and checks bRunning again).
	if (pRenderThread)
	{
		if (pRenderThread->joinable())
			pRenderThread->join();  // main thread waits for SimThread to complete

		delete pRenderThread;
		pRenderThread = NULL;
	}
}


void Renderer::Loop()
{
	while (bRunning)
	{
		// Render a frame
		RenderFrame();
	}
	map.Reset(); // set it inactive on the render thread, because a new thread will be created the next time we call Start()
}


void Renderer::RenderFrame()
{
	GameState & gs = pGame->GetGameState();
	map.pwindow->clear();
	map.pwindow->setActive(); // called on the render thread

	for (auto player : pGame->playerList)
	{
		lock_guard<mutex> c_lock(player->UM.GetMutex());
		// have to call a method on the UM, because its list of units is private.  I don't love this design.
		player->UM.Render(gs, map);
	}

	// TEST CODE - don't call this when the renderer for each unit is actually working because it clears the map!
	// map.TestDraw();

	map.pwindow->display();
}