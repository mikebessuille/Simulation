#pragma once

#include <mutex>
#include <thread>
#include <list>
#include <chrono>

using namespace std;
using namespace std::chrono;


template<typename T>
class MessageQueue
{
public:
	bool put(const T& val, milliseconds waitOnFull);
	void put(T&& val);
	bool get(T& val, milliseconds waitOnEmpty);


private:
	mutex mtx;
	condition_variable cond;
	list<T>queue;
	const unsigned int maxQueueSize = 500;
};


// These need to be in this header file, not in a separate .cpp file

// Returns true if get succeeds within time limit; false otherwise
template <typename T>
bool MessageQueue<T>::get(T& val, milliseconds waitOnEmpty)
{
	unique_lock<mutex> lock(mtx);
	bool notEmpty = cond.wait_for(lock, waitOnEmpty, [this] { return !queue.empty(); });  // the duration is there to avoid waiting forever if there is nothing to process
	if (notEmpty)
	{
		val = queue.front();
		queue.pop_front();
	}
	return(notEmpty);
}

// Returns true if put succeeds within time limit; false otherwise.
template <typename T>
bool MessageQueue<T>::put(const T& val, milliseconds waitOnFull)
{
	//  conditional wait to ensure this thread doesn't make the queue too big (if consumers can't keep up)
	unique_lock<mutex> lock(mtx);
	bool notFull = cond.wait_for(lock, waitOnFull, [this] { return queue.size() < maxQueueSize; });
	if (notFull)
	{
		queue.push_back(val);
		// Since we only added a single element to the queue, only notify one thread that is waiting on this conditional variable?  Rather than all threads?
		cond.notify_one();
	}
	return(notFull);
}