#include <memory>

using namespace std;

#pragma once
class CPP11SpecialFunctions
{
public:
	CPP11SpecialFunctions();
	virtual ~CPP11SpecialFunctions() = default;
	void run();
};


// TODO: Make use of that class in SpecialFunctions class.
// TODO: Add logging to the Resource struct's constructor & destructor?


// TODO: Instead of logging in the Resource struct, I could add custom allocator and deallocator 
// to shared & unique resource pointers in ResourceHandler, so that I can log when they get deleted.
// http://www.bfilipek.com/2016/04/custom-deleters-for-c-smart-pointers.html

struct Resource
{
public:
	int x;
	int y;
};


class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler() = default;
	
	// Copy operations
	ResourceHandler(const ResourceHandler&);
	ResourceHandler& operator=(const ResourceHandler&);

	// Move operations
	/*
	ResourceHandler(ResourceHandler&&);
	ResourceHandler& operator=(ResourceHandler&&);
	*/

private:
	int someResource{ 0 };
	shared_ptr<Resource> sharedResourcePtr{ nullptr };
	unique_ptr<Resource> exclusiveResourcePtr{ nullptr };
};