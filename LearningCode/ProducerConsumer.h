#pragma once

#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>

#include "MessageQueue.h"

class ProducerConsumer
{
public:
	ProducerConsumer();
	~ProducerConsumer();
	void run();
};


struct Message
{
	int id;
	string name;
	int* data[10]; // some data buffer contained in the message
};


class MessageHandler // : std::enable_shared_from_this< MessageHandler >
{
public:
	MessageHandler() = default;
	virtual ~MessageHandler() = default;
	virtual void ProduceMessages( std::function<bool(Message &)> creator );
	virtual void HandleMessages( std::function<bool(Message &)> handler );
	void Stop() { bRunning = false; };

private:
	MessageQueue<Message> mq;
	mutex cout_mtx; // for controlling console output
	atomic<bool> bRunning = true;
	atomic<unsigned int> currentID = 0; // atomic as there may be several producers.
};


class Producer
{
public:
	Producer() = default;
	virtual ~Producer() = default;
	bool CreateMessage( Message &msg);
	//void CreateMessage( shared_ptr<MessageHandler> pMsg, unsigned int id );
};

class Consumer
{
public:
	Consumer() = default;
	virtual ~Consumer() = default;
	bool HandleMessage(Message &msg);
};