#include "HealthComponentBasic.h"
#include <algorithm>

using namespace std;


HealthComponentBasic::HealthComponentBasic( unsigned int maxHealth ) : 
	HealthComponent( maxHealth )
{
}


HealthComponentBasic::~HealthComponentBasic()
{
}

void HealthComponentBasic::Update(GameState &gs, unsigned long nTick)
{
	// Not sure there is value in an Update method for the Health component?
	// Maybe to check if the unit has been destroyed, and remove it from the list?
}

// returns true if unit is still alive, false if it's destroyed
bool HealthComponentBasic::TakeDamage(unsigned int damage)
{
	// Careful to avoid overflow of the unsigned int...
	if (damage >= m_CurrentHealth)
	{
		m_CurrentHealth = 0;
		return(false);
	}
	else
	{
		m_CurrentHealth -= damage;
		return(true);
	}
}

void HealthComponentBasic::Heal(unsigned int health)
{
	m_CurrentHealth = min(m_MaxHealth, m_CurrentHealth + health);
}

