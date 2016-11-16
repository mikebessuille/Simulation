#include "stdafx.h"
#include "SuperBad.h"


const UnitDefaults SuperBad::defaults{	15.f, // default_size
										{ 250, 250, 0 }, // Yellow
										0, // default_points
										35, // default_damage
										50 // maxDestroyFrames
									};


SuperBad::SuperBad(sf::Vector2f pos, sf::Vector2f vel, const UnitDefaults *pdef ) : BadUnit(pos, vel, pdef )
{
	// Base ctor is called first, so shape is already created.
}


// Virtual; derived classes can override this with their appropriate different animation if they wish.
void SuperBad::RenderDestroyAnimation()
{
	BadUnit::RenderDestroyAnimation(); // Call parent

	pshape->scale(sf::Vector2f(1.08f, 1.08f)); // This will be applied after the scaling done in the base implementation
}


void SuperBad::RenderAnimation()
{
	BadUnit::RenderAnimation(); // Call parent

	sf::Color colour = pshape->getFillColor();
	if (bRenderColourIncreasing)
	{
		if (colour.r >= 255)
		{
			bRenderColourIncreasing = false;
			colour.r--;
		}
		else
		{
			colour.r++;
		}
	}
	else // bRenderColourIncreasing = false
	{
		if (colour.r == 0)
		{
			bRenderColourIncreasing = true;
			colour.r++;
		}
		else
		{
			colour.r--;
		}
	}
	pshape->setFillColor(colour);
}