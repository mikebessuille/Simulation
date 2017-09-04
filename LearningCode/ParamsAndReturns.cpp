#include "ParamsAndReturns.h"


Rational::Rational(int numerator, int denominator) : n(numerator), d(denominator)
{
}


// Returns a new Rational object.  This is defined outside of the Rational class, so that all cases of a*b work. (See item 24, Effective C++)
const Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return(Rational(lhs.numerator() * rhs.numerator(),
					lhs.denominator() * rhs.denominator()));
}

ParamsAndReturns::ParamsAndReturns()
{
}

Widget3 CreateWidget()
{
	return(Widget3(3, 4));
}

void ModifyWidget(Widget3 &w)
{
	// Modifies the widget being referenced.
	w.Set(5, 6);
}

void DoesNotModifyWidget(Widget3 w)
{
	w.Set(9, 10);
}

unique_ptr<Widget3> CreateNewWidgetPtr()
{
	return(make_unique<Widget3>(7, 8));
}

void ParamsAndReturns::run()
{
	cout << "ParamsAndReturns: run()" << endl;

	Rational oneEighth(1, 8);
	Rational oneHalf(1, 2);

	Rational result = oneHalf * oneEighth;
	result = result * oneEighth;
	result = 2 * oneHalf; // This would fail because of type conversion if operator* was a member of the Rational class
	result = oneHalf * 2; 


	// Different ways for functions to return objects, smart pointers to objects, or take reference to object as a param
	Widget3 w1 = CreateWidget(); // Creates a new widget and returns the object directly 
	ModifyWidget(w1); // Modifies the reference directly
	DoesNotModifyWidget(w1); // Uses a copy;
	shared_ptr<Widget3> pw = CreateNewWidgetPtr(); // Creates a ptr to a new widget object
}


