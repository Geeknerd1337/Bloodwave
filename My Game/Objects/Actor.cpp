#include "Actor.h"
#include "ComponentIncludes.h"


Actor::Actor(const Vector2& p) : CObject(eSprite::Player_Idle, p) {

} //constructor


void Actor::move() {
	const float t = m_pTimer->GetFrameTime(); //time
	m_vPos += t * m_vVelocity;
}

//take damage amount from health
void Actor::TakeDamage(int damage) {
	m_iHealth -= damage;
}
