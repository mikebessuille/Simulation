#include "stdafx.h"
#include "foo.h"

// Example file for PR-29218
foo::foo()
{
	pBar = new bar();
}


foo::~foo()
{
	delete pBar;
	pBar = NULL;
}
