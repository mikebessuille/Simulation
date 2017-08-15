
#include "MoveComponent.h"
#include "UnitBase.h"

bool MoveComponent::AtDestination(Point ptDest)
{
	if ((abs(m_parent->x - ptDest.x) < DISTANCE_THRESHOLD) &&
		(abs(m_parent->y - ptDest.y) < DISTANCE_THRESHOLD))
		return(true);
	else
		return(false);
}