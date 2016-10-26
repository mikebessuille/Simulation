#pragma once
class CPP11Features
{
public:
	CPP11Features();
	virtual ~CPP11Features();
	void run();

private:
	void UsingAuto();
	void UsingInitialization();
	void UsingAlias();
	void UsingNullptr();
	void UsingEnums();
	void UsingPointerTypes();

	// For nullptr example
	void foo(int);
	void foo(void*);
};

