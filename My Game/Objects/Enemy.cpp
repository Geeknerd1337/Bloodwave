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

	
	//starts in idle state, so set it to slow idle speed
	m_fMoveSpeed = 10.0f;

	SetSprite(eSprite::Enemy_Idle);
} //constructor

CEnemy::~CEnemy()
{
}



void CEnemy::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {}



void CEnemy::buildInput() {}

//reduce health by damage
//override from actor
void CEnemy::TakeDamage(int damage)
{
	m_iHealth -= damage;

	//if health is less than 0 mark as dead
	if (m_iHealth <= 0) {
		m_bDead = true;
	}
}

void CEnemy::handleIdle() {
	
	//every second, get a new random velocity
	//weighted towards standing still
	if ((m_pTimer->GetTime() - m_fIdleTime) > 1.0f) {
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
		m_vVelocity = idleVelocity * m_fIdleSpeed;

		//set idle time to new time
		m_fIdleTime = m_pTimer->GetTime();
	}
}

void CEnemy::handleChase() {
	//vector from player to enemy
	vEnemyToPlayer = m_pPlayer->GetPos()- m_vPos;

	//PERCY OR SAM: I am leaving this for you so you know how to check if an object is the player in your attack state, I had to test
	//because sometimes VS can get weird if it feels there's a circular dependency.
	/*if (dynamic_cast<CPlayer*>(m_pPlayer) != nullptr) {
		printf("I guess this worked?\n");
	}*/
	
	//if player is within chase radius, else return to idle
	//TO DO: figure out transition phase to chase state
		//printf("Chasing!\n");
		vEnemyToPlayer.Normalize();
		m_vVelocity = vEnemyToPlayer * m_fChaseSpeed;
	
}

//For now, handleTransitions only calls handleChase
void CEnemy::handleTransitions() {
	vEnemyToPlayer = m_pPlayer->GetPos() - m_vPos;
	if (enemyChaseRadius > vEnemyToPlayer.Length()) {
		m_eEnemyState = eEnemyState::Chase;
	}
	else {
		m_eEnemyState = eEnemyState::Idle;
	}
}

void CEnemy::handleAttack() {
	
}

void CEnemy::simulate() {
	
	//Finite state machine for dictating which manages the enemies state
	switch (m_eEnemyState) {
	case eEnemyState::Idle:
		//Enemy Idle State
		handleIdle();
		handleTransitions();
		break;
	case eEnemyState::Attack:
		//Enemy Attack State
		break;
	case eEnemyState::Chase:
		//Enemy Chase State
		handleChase();
		handleTransitions();
		break;
	case eEnemyState::Stun:
		//Enemy Stun State
		break;
	case eEnemyState::Dead:
		//Enemy Dead State
		break;
	}
}

