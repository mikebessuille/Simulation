
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
#include <random>


using namespace std;
using namespace std::chrono;
using std::placeholders::_1;

// This file implements a simple producer/consumer thread model.  The ProducerConsumer class just gets everything set up and started.
// The actual class that does most of the work is MessageHandler, which contains a list of all producers and consumers and
// owns the threads that execute loops to create or handle messages.
// The Producer and Consumer classes provide methods to create or handle a single message at a time, and are decoupled
// from the management of threads and from the management of the queue.


void ProducerConsumer::run()
{
	auto msg = make_shared<MessageHandler>();
	
	Producer Prod1, Prod2;
	Consumer Con1, Con2, Con3, Con4;

	// These objects register with the MessageHandler.
	msg->RegisterProducer(std::bind(&Producer::CreateMessage, Prod1, _1));
	msg->RegisterProducer(std::bind(&Producer::CreateMessage, Prod2, _1));

	msg->RegisterHandler(std::bind(&Consumer::HandleMessage, Con1, _1));
	msg->RegisterHandler(std::bind(&Consumer::HandleMessage, Con2, _1));
	msg->RegisterHandler(std::bind(&Consumer::HandleMessage, Con3, _1));
	msg->RegisterHandler(std::bind(&Consumer::HandleMessage, Con4, _1));

	// TODO:  how to handle if these objects (Prod1, Con1, etc) go out of scope and are deleted; but their handlers
	// are still in the MessageHandler list and still executing....
	// http://stackoverflow.com/questions/8711391/should-i-copy-an-stdfunction-or-can-i-always-take-a-reference-to-it
	// I would love for the Producer and Consumer classes to contain some kind of object that auto-registers itself,
	// and which auto-deregisters itself when it is destroyed.

	// Run threads until a key is hit.
	msg->Run();
	while (_kbhit() == 0) {}
	char ch = _getch(); // Clears the buffer... otherwise the next call to _kbhit() will immediately return true.
	msg->Stop();
}


// Utility function to return int between [0, max]
int random(int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());  // use random_device to seed the random generator from the operating system
	std::uniform_real_distribution<double> dist(0.0, max); // create a uniform distribution function with that range.
	return( static_cast<int>(dist(mt)));
}


void MessageHandler::ProduceMessages( const ProducerFunction & creator )
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

void MessageHandler::HandleMessages( const ConsumerFunction & handler )
{
	thread::id name = this_thread::get_id();

	// for testing, each consumer thread gets a random wait factor, to cause the threads to be out-of-order in the case of starvation
	int dur = random(200);  // between 0 and 200ms

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


void MessageHandler::RegisterProducer( const ProducerFunction & creator )
{
	// a reference to a bound object that binds the function and its original Producer object is passed into RegisterProducer.
	// I'm making a copy of that bound object to store in the pair, and in the producers vector.  Otherwise that bound object would
	// cease to exist when this method finishes.
	// This should not create a copy of the original Producer object.
	pair<ProducerFunction, shared_ptr<thread> > p = make_pair(creator, shared_ptr<thread>(nullptr));
	if (bRunning)
	{
		// Start this particular thread.
		p.second = make_shared<thread>(&MessageHandler::ProduceMessages, this, p.first );
	}
	producers.push_back(p);
}


void MessageHandler::RegisterHandler( const ConsumerFunction & handler )
{
	// ConsumerPair p = make_pair(handler, shared_ptr<thread>(nullptr));
	pair<ConsumerFunction, shared_ptr<thread> > p = make_pair(handler, shared_ptr<thread>(nullptr));

	if (bRunning)
	{
		// Start this particular thread.
		p.second = make_shared<thread>(&MessageHandler::HandleMessages, this, p.first);
	}
	consumers.push_back(p);
}


void MessageHandler::Run()
{
	if( !bRunning )
	{
		bRunning = true;
		// Start all the threads.
		// need to make sure this is a reference to a producer pair object, so it doesn't make a copy of the object and of its members.
		for (auto &&prod : producers )
		{
			if ( prod.second == nullptr)
			{
				prod.second = make_shared<thread>(&MessageHandler::ProduceMessages, this, prod.first);
			}
		}
		for (auto &&con : consumers )
		{
			if (con.second == nullptr)
			{
				con.second = make_shared<thread>(&MessageHandler::HandleMessages, this, con.first);
			}
		}
	}
}


void MessageHandler::Stop()
{
	if (bRunning)
	{
		bRunning = false;
		
		// Stop all the threads.
		for (auto &&prod : producers)
		{
			if (prod.second )
			{
				prod.second->join();
			}
		}
		for (auto &&con : consumers )
		{
			if (con.second)
			{
				con.second->join();
			}
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


