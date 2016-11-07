#pragma once
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>

using namespace std;

class CPP11Threads
{
public:
	CPP11Threads();
	~CPP11Threads();
	bool run();
	void DataModifier(int * a, int size);
	void DataValidator(int * a, int size);

private:
	mutex m_lock;
};
