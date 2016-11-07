#pragma once
#include <SFML\Graphics.hpp>

float VectorLength( const sf::Vector2f &vec);
float VectorLength( const sf::Vector2f &v1, const sf::Vector2f &v2);

void VectorNormalize(sf::Vector2f &vec);
float VectorDotProduct(const sf::Vector2f &v1, const sf::Vector2f &v2);
