#include "stdafx.h"

class BaseTest
{
public:
	BaseTest() : x(0)  {}
	virtual ~BaseTest() = 0;

private:
	int x;
};

class Derived : public BaseTest
{
public:
	Derived() : BaseTest(), y(0) {}
	~Derived() {}

private:
	int y;
};

class NestedClassTest
{
public:
	NestedClassTest()
	{
	}

	~NestedClassTest()
	{
	}

private:
	Derived d;
};
