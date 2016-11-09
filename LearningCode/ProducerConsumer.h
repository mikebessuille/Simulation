#pragma once

#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
#include <memory>
#include <vector>
#include <utility>

#include "MessageQueue.h"

using namespace std;

class ProducerConsumer
{
public:
	ProducerConsumer() = default;
	~ProducerConsumer() = default;
	void run();
};


struct Message
{
	int id;
	string name;
	int* data[10]; // some data buffer contained in the message
};

using ProducerFunction = std::function<bool(Message&)>;
using ConsumerFunction = std::function<bool(Message&)>;

using ProducerPair = pair<ProducerFunction &, unique_ptr<thread>>;
using ConsumerPair = pair<ConsumerFunction &, unique_ptr<thread>>;

class MessageHandler // : std::enable_shared_from_this< MessageHandler >
{
public:
	MessageHandler() = default;
	virtual ~MessageHandler() = default;
	virtual void ProduceMessages( const ProducerFunction &creator );
	virtual void HandleMessages( const ConsumerFunction &handler );

	void RegisterProducer( const std::function<bool(Message&)> &creator );
	void RegisterHandler( const ConsumerFunction &handler );
	void Run();
	void Stop();

private:
	MessageQueue<Message> mq;
	mutex cout_mtx; // for controlling console output
	atomic<bool> bRunning = false;
	atomic<unsigned int> currentID = 0; // atomic as there may be several producers.
	//vector<ProducerPair> producers; // Not sure why but this doesn't work with nested "using" definitions
	//vector<ConsumerPair> consumers;
	vector<pair<ProducerFunction &, unique_ptr<thread>>> producers;
	vector<pair<ConsumerFunction &, unique_ptr<thread>>> consumers;
};

// Producer and Consumer classes are coupled to the Messsage structure, but they are NOT coupled to
// the MessageHandler or the MessageQueue classes.
class Producer
{
public:
	Producer() = default;
	virtual ~Producer() = default;
	bool CreateMessage( Message &msg);
};

class Consumer
{
public:
	Consumer() = default;
	virtual ~Consumer() = default;
	bool HandleMessage(Message &msg);
};