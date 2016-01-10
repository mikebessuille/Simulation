#pragma once

#define SIM_API __declspec(dllexport) 

class SIM_API DLLClass
{
public:

	DLLClass() {};
	bool RunSimulation();
};