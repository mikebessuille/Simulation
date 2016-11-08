
/*  These are included in ProducerConsumer.h
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
#include "MessageQueue.h"
*/ 
#include "ProducerConsumer.h"
#include <conio.h>
#include <memory>


using namespace std;
using namespace std::chrono;
using std::placeholders::_1;

// This file implements a simple producer/consumer thread model.  The ProducerConsumer class just gets everything set up and started.
// The actual classes that do the work are called Producer and Consumer, and they start their work threads as soon as they are constructed.
ProducerConsumer::ProducerConsumer()
{
}

ProducerConsumer::~ProducerConsumer()
{
}

void ProducerConsumer::run()
{
	auto msg = make_shared<MessageHandler>();
	
	Producer Prod1, Prod2;
	Consumer Con1, Con2, Con3, Con4;

	// Create multiple consumer threads and a single producer thread.
	thread t_p1(&MessageHandler::ProduceMessages, msg.get(), std::bind(&Producer::CreateMessage, Prod1, _1) );
	thread t_p2(&MessageHandler::ProduceMessages, msg.get(), std::bind(&Producer::CreateMessage, Prod2, _1));

	thread t_c1(&MessageHandler::HandleMessages, msg.get(), std::bind(&Consumer::HandleMessage, Con1, _1));
	thread t_c2(&MessageHandler::HandleMessages, msg.get(), std::bind(&Consumer::HandleMessage, Con2, _1));
	thread t_c3(&MessageHandler::HandleMessages, msg.get(), std::bind(&Consumer::HandleMessage, Con3, _1));
	thread t_c4(&MessageHandler::HandleMessages, msg.get(), std::bind(&Consumer::HandleMessage, Con4, _1));

	// Run threads until a key is hit.
	while (_kbhit() == 0) {}
	char ch = _getch(); // Clears the buffer... otherwise the next call to _kbhit() will immediately return true.
	msg->Stop();

	// Clean up, stop the threads (waits for the thread to finish and then kills it)
	t_p1.join();
	t_p2.join();
	t_c1.join();
	t_c2.join();
	t_c3.join();
	t_c4.join();
}


// Utility function to return int between [0, max]
int random(int max, unsigned int seed)
{
	// TODO: Use threadsafe random methods in CPP11 <random> ???

	std::srand(seed); // use current time as seed for random generator
	float val = static_cast<float> (std::rand()) * static_cast<float>(max) / static_cast<float> (RAND_MAX);
	return(static_cast<int>(val));
}


// void MessageHandler::ProduceMessages( std::function<bool(shared_ptr<MessageHandler>, unsigned int)> func )
void MessageHandler::ProduceMessages( std::function<bool(Message &)> creator )
{
	// shared_ptr<MessageHandler> pMsg = shared_from_this();
	while (bRunning)
	{
		Message msg;
		msg.id = currentID;
		if (creator(msg))
		{
			if (mq.put(msg, milliseconds(100)))
			{
				// put succeeded.
				++currentID;
			}
			else
			{
				// Queue is full
				lock_guard<mutex> c_lock(cout_mtx);
				cout << "Producer:  ***** QUEUE IS FULL ***** " << endl;
			}
		}
		/*
		// For testing:  Force consumer threads to starve.
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		*/
	}
}

void MessageHandler::HandleMessages(std::function<bool(Message&)> handler )
{
	thread::id name = this_thread::get_id();

	// for testing, each consumer thread gets a random wait factor, to cause the threads to be out-of-order in the case of starvation
	unsigned int seed = std::hash<std::thread::id>()(name); // use the thread id as the seed to the random number generator
	int dur = random(200, seed);  // between 0 and 200ms

	while (bRunning)
	{
		Message msg;
		if (mq.get(msg, milliseconds(dur)))
		{
			if (handler(msg))
			{
				// Print the thread ID and the Message ID here
				lock_guard<mutex> c_lock(cout_mtx);
				cout << "Thread: " << name << "    Processing: " << msg.id << endl;

				// for testing, each consumer thread takes a random amount of time to process each message, in order to cause the threads to be out-of-order.
				std::this_thread::sleep_for(std::chrono::milliseconds(dur / 10)); // between 0 and 20 ms
			}
			else
			{
				// Error!  failed to process message, but it was removed from the queue.
			}
		}
		else
		{
			// Nothing to process; this thread would be starving, if it wasn't implemented with conditional wait_for() in the get method.
			lock_guard<mutex> c_lock(cout_mtx);
			cout << "Thread: " << name << "    Nothing to process..." << endl;
		}
	}
}


// Creates a single message
bool Producer::CreateMessage( Message &msg )
{
	msg.name = "Mike";
	return(true);
}


// Handle a single message
bool Consumer::HandleMessage( Message &msg )
{
	return(true);
}


