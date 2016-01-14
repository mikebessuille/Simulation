#pragma once

// Don't define this if we're using the library as a static library
// #define SIM_API __declspec(dllexport) 
#define SIM_API

class SIM_API DLLClass
{
public:

	DLLClass() {};
	bool RunSimulation();
};