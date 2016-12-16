#include "CPP11AsyncTasks.h"
#include <iostream>

using namespace std;


CPP11AsyncTasks::CPP11AsyncTasks()
{
}


CPP11AsyncTasks::~CPP11AsyncTasks()
{
}


bool CPP11AsyncTasks::run()
{
	int myArray[10];

	cout << "CPP11AsyncTasks: run()" << endl;

	// These may be both run on the same thread, or different threads...
	// must capture the return of each async call (as a "future") or else the first call to async will block the second call.
	auto futureVal = async(&CPP11AsyncTasks::DataValidator, this, myArray, 10);
	auto futureMod = async(&CPP11AsyncTasks::DataModifier, this, myArray, 10);

	return( futureVal.get() && futureMod.get()); // return true if both methods returned true.
}


bool CPP11AsyncTasks::DataModifier(int * a, int size)
{
	for (int i = 1; i < size; ++i)
	{
		{	// Extra braces to introduced scope
			// Locks the mutex while in scope.  When the lock_guard object goes out of scope, it releases the mutex.
			lock_guard<mutex> lock1(m_lock);

			a[i] = i;
		}
		this_thread::sleep_for(chrono::milliseconds(200)); // when run with async, will this cause "Whatever thread in the thread pool
															// which is executing this method" to sleep?
	}
	return(true);
}


bool CPP11AsyncTasks::DataValidator(int * a, int size)
{
	int max = 0;
	int loop = 0; // to protect against this running forever.
	const int loopMax = 1000;
	bool ret = true;

	do
	{
		{ // for scope of mutex lock
			lock_guard<mutex> lock1(m_lock);

			for (int i = 1; i < size; ++i)
			{
				if (a[i] > max)
					max = a[i];
			}
		}
		loop++;
		cout << "Max value: " << max << endl;
	} while (max < 6 && loop < loopMax);
	if (loop >= loopMax)
	{
		cout << "Error:  Max number of loops reached." << endl;
		ret = false;
	}
	return(ret);
}