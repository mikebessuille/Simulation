#include "PimplPattern.h"
#include <memory>
#include <vector> // Notice that these are not included in PimplPattern.h
#include <string>

using namespace std;

// Define the implementation first:
struct PimplPattern::Impl
{
	// by default these are public, and accessible within the PimplPattern class through the pImpl unique_ptr.
	string name;
	vector<double> data;
};


PimplPattern::PimplPattern() : pImpl(make_unique<Impl>())
{
}


// Must define the destructor in the CPP file, not in the header file, or we'll get undefined type "PimplPattern::Impl" 
// when the compiler tries to create a default destructor there.
// pImpl unique pointer will be deconstructed automatically (there is only one!) and the Impl will be deconstructed as a result.
PimplPattern::~PimplPattern() = default; 

void PimplPattern::run()
{
	pImpl->name = "Superman";
	pImpl->data.push_back(3.0);
}



