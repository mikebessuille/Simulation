#include "stdafx.h" // must be the first line, when using pre-compiled headers
#include "main.h"
#include "GameController.h"


// This main is never called; winmain in sfmlgame.cpp overrides it somehow.
int main()
{
	return(mainSFML());
}


int mainSFML()
{
	GameController gc;
	gc.GameLoop();

	return 0;
}
