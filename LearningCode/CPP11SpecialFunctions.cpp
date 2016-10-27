#include "CPP11SpecialFunctions.h"


CPP11SpecialFunctions::CPP11SpecialFunctions()
{
}


void CPP11SpecialFunctions::run()
{
	cout << "Special Functions: run()" << endl;
	ResourceHandler resA;
	ResourceHandler resB;
	ResourceHandler resC(resA); // Copy Constructor
	ResourceHandler resD;
	resD = resB; // Copy assignment operator

}




ResourceHandler::ResourceHandler()
{
	sharedResourcePtr = make_shared<Resource>(); // May be deleted by default destructor, if no other ResourceHandler points to it.
	exclusiveResourcePtr = make_unique<Resource>(); // deleted by default destructor automatically.
}


// Copy Constructor
ResourceHandler::ResourceHandler(const ResourceHandler &rhs)
{
	// Shared Resource
	sharedResourcePtr = rhs.sharedResourcePtr; // Copy the rhs's shared pointer

	// Exclusive Resource
	exclusiveResourcePtr = make_unique<Resource>(); // allocate a new unique Resource
	*exclusiveResourcePtr = *(rhs.exclusiveResourcePtr); // copy the value of original exclusive resource into new exclusive resource.
}


// Copy Assignment
ResourceHandler & ResourceHandler::operator=(const ResourceHandler &rhs)
{
	if (this != &rhs) // protect against invalid self-assignment
	{
		// Shared Resource
		sharedResourcePtr = rhs.sharedResourcePtr; // Copy the rhs's shared pointer

		// Exclusive Resource
		exclusiveResourcePtr = make_unique<Resource>(); // allocate a new unique Resource; may also deallocate whatever the LHS's exclusive ptr used to point to.
		*exclusiveResourcePtr = *(rhs.exclusiveResourcePtr); // copy the value of original exclusive resource into new exclusive resource.
	}
	return *this;
}


// TODO: https://msdn.microsoft.com/en-us/library/dd293665.aspx?f=255&MSPPError=-2147217396
/*
// Move Constructor
ResourceHandler::ResourceHandler(ResourceHandler &&rhs)
{
}


// Move Assignment
ResourceHandler & ResourceHandler::operator=(ResourceHandler &&rhs)
{
	// TODO: insert return statement here
}
*/
