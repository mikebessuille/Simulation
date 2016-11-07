#include "stdafx.h"
#include "VectorUtils.h"

// Utility functions... (pass by reference or we'll end up changing a copy!)
float VectorLength(const sf::Vector2f &vec)
{
	// Take care of case where length is 0; don't want to normalize it to be huge!
	if (vec.x == 0.f)
		return(vec.y); // this also covers the case where they're both 0
	if (vec.y == 0.f)
		return(vec.x);
	return(sqrt((vec.x * vec.x) + (vec.y * vec.y)));
}


float VectorLength(const sf::Vector2f &v1, const sf::Vector2f &v2 )
{
	if (v1.x == v2.x && v1.y == v2.y)
		return(0.f);
	else if (v1.x == v2.x)
		return(abs(v2.y - v1.y));
	else if (v1.y == v2.y)
		return(abs(v2.x - v1.x));
	else
		return(sqrt((v2.x-v1.x)*(v2.x-v1.x) + (v2.y-v1.y)*(v2.y-v1.y)));
}


void VectorNormalize(sf::Vector2f &vec)
{
	float magnitude = VectorLength(vec);
	if (magnitude > 0.f)
		vec /= magnitude;
	if (vec.x > 1.f)
		vec.x = 1.f;
	else if (vec.x < -1.f)
		vec.x = -1.f;
	if (vec.y > 1.f)
		vec.y = 1.f;
	else if (vec.y < -1.f)
		vec.y = -1.f;
}

float VectorDotProduct(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
	return((v1.x * v2.x) + (v1.y * v2.y));
}
