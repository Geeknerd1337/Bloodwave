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

	m_pIdleEvent = new LEventTimer(1.0f);
	//starts in idle state, so set it to slow idle speed
	m_fMoveSpeed = 10.0f;

	SetSprite(eSprite::Enemy_Idle);
} //constructor



void CEnemy::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {}

const Vector2& CEnemy::GetPos() const {
	return m_vPos;
} //GetPos

void CEnemy::buildInput() {}

void CEnemy::handleIdle() {
	
	//every second, get a new random velocity
	//weighted towards standing still
	if (m_pIdleEvent && m_pIdleEvent->Triggered()) {
		randomNumber = m_pRandom->randf();
		if (randomNumber < 0.1f) {
			idleVelocity = Vector2(0, 1);
		}
		else if (randomNumber < 0.2f) {
			idleVelocity = Vector2(1, 0);
		}
		else if (randomNumber < 0.3f) {
			idleVelocity = Vector2(1, 1);
		}
		else if (randomNumber < 0.4f) {
			idleVelocity = Vector2(-1, 0);
		}
		else if (randomNumber < 0.5f) {
			idleVelocity = Vector2(0, -1);
		}
		else if (randomNumber < 0.6f) {
			idleVelocity = Vector2(-1, -1);
		}
		else {
			idleVelocity = Vector2(0, 0);
		}
		m_vVelocity = idleVelocity * m_fMoveSpeed;
	}
}

void CEnemy::simulate() {
	
	//Finite state machine for dictating which manages the enemies state
	switch (m_eEnemyState) {
	case eEnemyState::Idle:
		handleIdle();
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
