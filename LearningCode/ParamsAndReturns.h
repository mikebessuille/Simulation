#pragma once

#include <memory>
#include <iostream>

using namespace std;


// See Effective C++, items 21 and 24
class Rational
{
public:
	Rational() = delete;
	Rational(int numerator = 0, int denominator = 1);
	~Rational() = default;
	int numerator() const { return(n); };
	int denominator() const { return(d); };
private:
	int n, d;
};

// Define as a non-member function
const Rational operator*(const Rational& lhs, const Rational& rhs);


class Widget3
{
public:
	Widget3() = default;
	Widget3(int x_, int y_) : x(x_), y(y_) {};
	~Widget3() = default;
	void Set(int x_, int y_) {
		x = x_; y = y_;
	};

private:
	int x{ 0 }, y{ 0 };
};

Widget3 CreateWidget();
void ModifyWidget(Widget3 &w);
void DoesNotModifyWidget(Widget3 w);
unique_ptr<Widget3> CreateNewWidgetPtr();

class ParamsAndReturns
{
public:
	ParamsAndReturns();
	virtual ~ParamsAndReturns() = default;
	void run();
};


