#include "Game.h"

// Game class to hold the simulation, players, etc.

Game::Game() : sim(this)
{
	// TODO: initialize each player's Unit Manager

}


Game::~Game()
{
}








/*
Doesn't belong here...

*/

/*
using namespace std;

mutex ThreadingErr::LockA;
mutex ThreadingErr::LockB;


ThreadingErr::ThreadingErr()
{
}


ThreadingErr::~ThreadingErr()
{
}


STATIC_INIT(ThreadingErr)
{
	std::cout << "I'm the static initialization block of ThreadingErr\n";
	// create a new instance of myself (this will only happen once)
	new ThreadingErr; // Constructor registers this (so it's not leaked).
}


void ThreadingErr::DataModifier(int * a, int size)
{
	for (int i = 1; i < size; ++i)
	{
		{	// Extra braces to introduced scope
			// Locks the mutex while in scope.  When the lock_guard object goes out of scope, it releases the mutex.
			lock_guard<mutex> lock(LockA);
			lock_guard<mutex> lock(LockB);

			a[i] = i;
		}
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}


void ThreadingErr::DataValidator(int * a, int size)
{
	int max = 0;

	do
	{
		{ // for scope of mutex lock
		  // Lock in opposite order from DataModifier(), to generate KW CONC.DL error  (Concurrency: deadlock)
			lock_guard<mutex> lock(LockB);
			lock_guard<mutex> lock(LockA);

			for (int i = 1; i < size; ++i)
			{
				if (a[i] > max)
					max = a[i];
			}
		}
		cout << "Max value: " << max << endl;
	} while (max < 6);
}

void NonMemberFunction(int * a, int size)
{
	// todo
}

bool ThreadingErr::RunErrors()
{
	int myArray[10];
	thread t_runner(&ThreadingErr::DataModifier, this, myArray, 10);  // Creates new thread and runs Modifier method.
	thread t_validator(&ThreadingErr::DataValidator, this, myArray, 10);  // Creates new thread and runs Validator method.
	thread t_nonMember(NonMemberFunction, myArray, 10);	// Create a new thread with a non-member function.

														// Clean up, stop the threads (waits for the thread to finish and then kills it)
	t_runner.join();
	t_validator.join();
	t_nonMember.join();
	return(true);
}

*/