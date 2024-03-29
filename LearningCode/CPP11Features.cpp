#include "CPP11Features.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>
#include <cassert>

#include "Widget.h"

using namespace std;

CPP11Features::CPP11Features()
{
}


CPP11Features::~CPP11Features()
{
}

void CPP11Features::run()
{
	UsingAuto();
	UsingInitialization();
	UsingAlias();
	UsingNullptr();
	UsingEnums();
	UsingPointerTypes();
}

int MethodReturnTypeMayChange()
{
	return(3);
}


class Something // A local class which is defined only in the scope of this compilation unit (file).
{
public:
	Something(int x, int y) : m_x(x), m_y(y) {};
	~Something() {};
	void increment() { m_x++; m_y++; };
	int getSum() { return m_x + m_y; }
private:
	int m_x{ 0 }, m_y{ 0 };
};

void printVector(vector<Something> vec, string heading )
{
	cout << heading << ": ";
	for (Something it : vec)
	{
		cout << it.getSum() << " : ";
	}
	cout << endl;
}

void UsingAutoIterators()
{
	vector<Something> vec{ { 1,2 },{ 3,4 },{ 5,6 },{ 7,8 } };
	cout << "Auto as Iterators ***************** " << endl;
	printVector(vec, "Original ");

	// This makes a copy of each "Something" object and modifies the copy:
	for (auto it : vec)
	{
		it.increment();
	}
	printVector(vec, "auto it  ");

	// This uses auto but explicitly asks for a reference, so it doesn't make copies.  Actually modifies the elements in the vector.
	for ( auto& it: vec )
	{
		it.increment();
	}
	printVector(vec, "auto ref ");

	// Alternative that avoids auto and actually modifies the elements in the vector:
	for (Something& it : vec)
	{
		it.increment();
	}
	printVector(vec, "Reference");
}

void CPP11Features::UsingAuto()
{
	cout << "Auto ******************** " << endl;

	vector<int> v{ 1,3,5,7 };
	auto vectorSize = v.size(); // size_t
	cout << "Vector size (expecting 4):" << vectorSize << endl;
	for (auto it : v)
	{
		// in this case, "it" is an int
		cout << "    Value:" << it << endl;
	}

	// Using auto here will avoid having to change code that uses a method whose signature may change due to refactoring.
	auto val = MethodReturnTypeMayChange();

	UsingAutoIterators();
}

// Tests initialization of a more complex object in a list
void TestObjectInitialization()
{
	class Widget2 // A local class which is defined only in the scope of this function.
	{
	public:
		Widget2(int x, int y) : m_x(x), m_y(y) {};
		~Widget2() {};
		int getSum() { return m_x + m_y;  }
	private:
		int m_x{ 0 }, m_y{ 0 };
	};

	// A vector of Widgets.  Each inner {} specifies the values sent to one Widget constructor.
	vector<Widget2> wv{ {1,2}, {3,4}, {5,6}, {7,8} };
	size_t vectorSize = wv.size();
	assert(vectorSize == 4);
	cout << "Widget2 Vector size (expecting 4):" << vectorSize << endl;
	cout << "Widget2 Sizes:" << endl;
	for (auto it : wv )
	{
		// Note that "it" in this case contains a copy of each Widget in the vector; I don't think it points to the original widget.
		cout << "    Widget2 Sum:" << it.getSum() << endl;
	}
}

void CPP11Features::UsingInitialization()
{
	cout << "Initialization ******************** " << endl;

	// simple types; these all initialize in the same way.
	int x(3);
	int y = 4;
	int z{ 5 };

	// list initialization
	vector<int> v{ 1,3,5,7 };
	size_t vectorSize = v.size();
	assert(vectorSize == 4);
	cout << "Vector size (expecting 4):" << vectorSize << endl;

	// Uses non-std::initializer_list ctor; constructs a 10-element vector where all elements have value 20
	vector<int>v1(10, 20);
	vectorSize = v1.size();
	assert(vectorSize == 10);
	cout << "Vector size (expecting 10):" << vectorSize << endl;

	// Uses std::initializer_list ctor; 2-element vector, with values of 10 and 20.
	vector<int>v2{ 10,20 };
	vectorSize = v2.size();
	assert(vectorSize == 2);
	cout << "Vector size (expecting 2):" << vectorSize << endl;

	// objects
	TestObjectInitialization();
}

void CPP11Features::UsingAlias()
{
	cout << "Alias ******************** " << endl;

	// OLD:
	// typedef unordered_map<string, string> StringMap;
	
	// NEW:
	using StringMap = unordered_map<string, string>;
	StringMap teamList {	{ "Ottawa", "Sens" },
							{ "Toronto", "Leafs" } };
	unsigned int numTeams = static_cast<unsigned int>(teamList.size());
	assert( numTeams == 2);
	cout << "Num Teams (expecting 2):" << numTeams << endl;
	
}

void CPP11Features::foo(int x) { cout << "foo(int) called" << endl;  }
void CPP11Features::foo(void *ptr) { cout << "foo(void*) called" << endl; }

void CPP11Features::UsingNullptr()
{
	cout << "Nullptr ******************** " << endl;
	// Always use nullptr instead of NULL or 0.

	cout << "Using NULL:  ";
	foo(NULL);
	cout << "Using 0:  ";
	foo(0);
	cout << "Using nullptr:  ";
	foo(nullptr);
}

void CPP11Features::UsingEnums()
{
	cout << "Enums ******************** " << endl;

	enum OldColor { white, black, red };
	// auto white = false;  // This would not compile, as "white" is already in scope.
	OldColor c1 = black;

	enum class NewColor { white, black, red };
	NewColor c2 = NewColor::white;
	auto c3 = NewColor::red;

	// Different type (must be an integer-type)
	enum class StatusCode: unsigned int {
								Running = 3,
								Startup = 2,
								Failed = 9 
								};

	auto status = StatusCode::Failed;
	cout << "Status Code (Expecting 9): " << static_cast<unsigned int>(status) << endl;
}


unique_ptr<Widget> FactoryMethod( int x )
{
	unique_ptr<Widget> pw = make_unique<Widget>(x);
	return( pw );
}

void CPP11Features::UsingPointerTypes()
{
	cout << "Smart Pointers ******************** " << endl;

	// Different ways of constructing a shared pointer:
	shared_ptr<Widget> p1(new Widget(3));
	auto p2 = make_shared<Widget>(3);

	// This isn't as good as passing new directly to the shared_ptr ctor, because people may use (or delete!) the raw pointer,
	// which would mess up the shared_ptr because its reference count will not be zero and it will point to deleted memory!
	Widget * rawPtr = new Widget(3);
	shared_ptr<Widget> p3(rawPtr);
	// delete rawPtr;  // If we did this, when p3 goes out of scope it will delete the same memory twice...  BAD...

	// Using a factory method which returns a unique_ptr, but converting it to a shared_ptr.
	shared_ptr<Widget> p4 = FactoryMethod(3);

}