#pragma once
class SocketClass
{
public:
	SocketClass();
	virtual ~SocketClass();

	int TestMethod() { return 3; };

private:
	int test1 = 0;	// Remove!
	int test2 = 0;	// Remove!
};

