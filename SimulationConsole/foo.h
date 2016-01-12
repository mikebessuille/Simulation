#pragma once

struct bar
{
	int a;
	int b;
};

class foo
{
public:
	foo();
	~foo();

private:
	bar* pBar;
	foo& operator=(const foo&) { return *this; }
	foo(const foo& src) { }
};

