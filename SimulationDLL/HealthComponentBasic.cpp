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

}

// returns true if unit is still alive, false if it's destroyed
bool HealthComponentBasic::TakeDamage(unsigned int damage)
{
	m_CurrentHealth = max((unsigned int)0, m_CurrentHealth - damage);
	if (m_CurrentHealth == 0)
		return false;
	else
		return true;
}

void HealthComponentBasic::Heal(unsigned int health)
{
	m_CurrentHealth = min(m_MaxHealth, m_CurrentHealth + health);
}

