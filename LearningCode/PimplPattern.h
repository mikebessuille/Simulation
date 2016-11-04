#pragma once

#include <memory>

// This class implements the Pimpl (pointer to Implementation) pattern.  Notice that the data members of the class are hidden from the declaration of the class,
// and therefore this header file is not coupled with header files of the implementation details.  Users of this header file are completely removed from the
// implementation details of the class.

class PimplPattern
{
public:
	PimplPattern();
	~PimplPattern();
	void run();
	
private:
	struct Impl; // just declares it, and only within the scope of this class.
	std::unique_ptr<Impl> pImpl;
};

