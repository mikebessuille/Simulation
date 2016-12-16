#pragma once

#include "CPP11Threads.h"
#include <future>

class CPP11AsyncTasks
{
public:
	CPP11AsyncTasks();
	~CPP11AsyncTasks();
	bool run();
	bool DataModifier(int * a, int size);
	bool DataValidator(int * a, int size);

private:
	mutex m_lock;
};

