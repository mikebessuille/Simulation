
#include "MoveComponent.h"
#include "UnitBase.h"


const double MoveComponent::distance_threshold = 0.5;

bool MoveComponent::AtDestination(Point ptDest)
{
	if ((abs(m_parent->x - ptDest.x) < distance_threshold) &&
		(abs(m_parent->y - ptDest.y) < distance_threshold))
	{
		return(true);
	}
	else
	{
		return(false);
	}
}