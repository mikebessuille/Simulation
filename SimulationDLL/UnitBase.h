#pragma once
class UnitBase
{
public:
	UnitBase();
	virtual ~UnitBase();
	void Action( unsigned long nTick );

// Member Variables
private:
	unsigned long nLastUpdateTick;

public:
	double x, y;
	double dx, dy;
};

