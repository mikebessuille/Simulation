#pragma once
#include "Order.h"
#include "UnitBase.h"


class OrderAttack :
	public Order
{
public:
	OrderAttack() = delete;
	OrderAttack(UnitBase *pTarget );
	virtual ~OrderAttack();
	bool Execute(GameState &gs, UnitBase * punit);

private:
	UnitBase *m_pTarget;
};

