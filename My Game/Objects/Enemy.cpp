/// \file Enemy.cpp
/// \brief Code for the enemy object class CEnemy.

#include "Enemy.h"
#include "ComponentIncludes.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"


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
		DeathFX();
	}
}


//display death sprite and death effects
void CEnemy::DeathFX() {
	LParticleDesc2D d; //particle descriptor
	d.m_vPos = m_vPos; //center particle at turret center

	//set sprite and particle settings
	d.m_nSpriteIndex = (UINT)eSprite::Enemy_Dead;
	d.m_fLifeSpan = 2.0f;
	d.m_fMaxScale = 1.0f;
	d.m_fScaleInFrac = 0.0f;
	d.m_fFadeOutFrac = 0.8f;
	d.m_fScaleOutFrac = 0;
	m_pParticleEngine->create(d);

	
} //DeathFX

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
	vEnemyToPlayer = m_pPlayer->GetPos() - m_vPos;

	vEnemyToPlayer.Normalize();
	m_vVelocity = vEnemyToPlayer * m_fChaseSpeed;
	
}

void CEnemy::handleTransitions() {
	vEnemyToPlayer = m_pPlayer->GetPos() - m_vPos;

	//if player is within chase radius change state to chase, else return to idle
	if (enemyChaseRadius > vEnemyToPlayer.Length()) {
		m_eEnemyState = eEnemyState::Chase;
	}
	else {
		m_eEnemyState = eEnemyState::Idle;
	}

	//if player is within attack radius, check if an object is the player, then set state to attack
	if (enemyAttackRadius > vEnemyToPlayer.Length()) {
		if (dynamic_cast<CPlayer*>(m_pPlayer) != nullptr) {
			m_eEnemyState = eEnemyState::Attack;
		}
	}
}

void CEnemy::handleAttack() {
	//get player health
	int playerHealth = m_pPlayer->getPlayerHealth();
	
	//attack every second
	if ((m_pTimer->GetTime() - m_fAttackTime) > 1.0f) {
		//if player health is > 0, attack
		if (playerHealth > 0) {
			m_pPlayer->TakeDamage(15);
		}

		//return to idle after player death
		m_eEnemyState = eEnemyState::Idle;

		//set idle attack to new time
		m_fAttackTime = m_pTimer->GetTime();
	}
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
		handleAttack();
		handleTransitions();
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

