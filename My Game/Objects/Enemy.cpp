/// \file Enemy.cpp
/// \brief Code for the enemy object class CEnemy.

#include "Enemy.h"
#include "ComponentIncludes.h"
#include "Helpers.h"

CEnemy::CEnemy(const Vector2& p) : Actor(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so enemy is standing upright
	m_fRoll = 0.0;

	SetSprite(eSprite::Enemy_Idle);
} //constructor



void CEnemy::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {}

const Vector2& CEnemy::GetPos() const {
	return m_vPos;
} //GetPos

void CEnemy::buildInput() {}

void CEnemy::simulate() {
	
	//Finite state machine for dictating which manages the enemies state
	switch (m_eEnemyState) {
	case eEnemyState::Idle:
		//Enemy Idle State
		break;
	case eEnemyState::Attack:
		//Enemy Attack State
		break;
	case eEnemyState::Chase:
		//Enemy Chase State
		break;
	case eEnemyState::Stun:
		//Enemy Stun State
		break;
	case eEnemyState::Dead:
		//Enemy Dead State
		break;
	}
}
