#include "CPP11Threads.h"
#include <iostream>

using namespace std;


void CPP11Threads::DataModifier(int * a, int size)
{
	for (int i = 1; i < size; ++i)
	{
		{	// Extra braces to introduced scope
			// Locks the mutex while in scope.  When the lock_guard object goes out of scope, it releases the mutex.
			lock_guard<mutex> lock1(m_lock);

			a[i] = i;
		}
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}


void CPP11Threads::DataValidator(int * a, int size)
{
	int max = 0;

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
		cout << "Max value: " << max << endl;
	} while (max < 6);
}


bool CPP11Threads::run()
{
	int myArray[10];

	cout << "CPP11Threads: run()" << endl;

	thread t_runner(&CPP11Threads::DataModifier, this, myArray, 10);  // Creates new thread and runs Modifier method.
	thread t_validator(&CPP11Threads::DataValidator, this, myArray, 10);  // Creates new thread and runs Validator method.

	// Clean up, stop the threads (waits for the thread to finish and then kills it)
	t_runner.join();
	t_validator.join();

	return(true);
}