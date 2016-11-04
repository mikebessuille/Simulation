#pragma once

class Widget
{
public:
	Widget() {};
	Widget(int _x) : x(_x) {};
	~Widget() = default;

private:
	int x{ 3 };
	int y{ 4 };

};