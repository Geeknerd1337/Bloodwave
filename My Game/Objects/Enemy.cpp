/// \file Enemy.cpp
/// \brief Code for the enemy object class CEnemy.

#include "Enemy.h"
#include "ComponentIncludes.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include <cmath>


CEnemy::CEnemy(const Vector2& p) : Actor(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so enemy is standing upright
	m_fRoll = 0.0;

	
	//starts in idle state, so set it to slow idle speed
	m_fMoveSpeed = 10.0f;

	SetSprite(eSprite::Enemy_Idle);
	
	m_fImageSpeed = 60 * 0.50f;
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

	//Get the direction to the player
	Vector2 dir = (m_pPlayer->m_vPos - m_vPos);
	dir.Normalize();
	m_vstunDirection = dir * -1.0f;
	
	m_tTimeSinceStunned.SetTimeSince(0.0f);

	SetState(eEnemyState::Stun);

	//if health is less than 0 mark as dead
	if (m_iHealth <= 0) {
		m_bDead = true;
		DeathFX();
	}
}

void CEnemy::HandleStun() {
	if (m_tTimeSinceStunned.GetTimeSince() < m_fStunTime) {
		m_vVelocity = m_vstunDirection * m_fStunSpeed;

		//Get the sin using m_ptimer
		float sin = std::sin(m_pTimer->GetTime() * 100.0f);

		if (sin > 0) {
			//Set the image tint to red
			m_f4Tint = Vector4(1.0, 0.0, 0.0, 1.0);
		}
		else {
			m_f4Tint = Vector4(1.0, 1.0, 1.0, 1.0);
		}
	}
	else {
		SetState(eEnemyState::Idle);
		m_f4Tint = Vector4(1.0, 1.0, 1.0, 1.0);
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

void CEnemy::HandleIdle() {
	
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

void CEnemy::HandleChase() {
	//vector from player to enemy
	vEnemyToPlayer = m_pPlayer->GetPos() - m_vPos;

	vEnemyToPlayer.Normalize();
	m_vVelocity = vEnemyToPlayer * m_fChaseSpeed;
	
}

void CEnemy::HandleWalk() {
	
	if (m_vVelocity.x != 0.0f) {
		if (m_vVelocity.x > 0.0f) {
			SetSprite(eSprite::Enemy_Walk_Right);
		}

		if (m_vVelocity.x < 0.0f) {
			SetSprite(eSprite::Enemy_Walk_Left);
		}
	}
	
	if (m_vVelocity.x == 0.0f) {
		SetSprite(eSprite::Enemy_Idle);
	}
	
}

void CEnemy::HandleTransitions() {
	vEnemyToPlayer = m_pPlayer->GetPos() - m_vPos;

	//enemy chases player until a certain radius, else return to idle
	if (enemyChaseRadius < vEnemyToPlayer.Length()) {
		SetState(eEnemyState::Chase);
	}
	else {
		SetState(eEnemyState::Idle);
	}

	//if player is within attack radius, check if an object is the player, then set state to attack
	if (enemyAttackRadius > vEnemyToPlayer.Length()) {
		if (dynamic_cast<CPlayer*>(m_pPlayer) != nullptr) {
			SetState(eEnemyState::Attack);
		}
	}

}

void CEnemy::HandleAttack() {
	//get player health
	int playerHealth = std::floor(m_pPlayer->getPlayerHealth());
	
	//attack every second
	if ((m_pTimer->GetTime() - m_fAttackTime) > 1.0f) {
		//if player health is > 0, attack
		if (playerHealth > 0) {
			m_pPlayer->TakeDamage(m_iAttackPoints);
		}
		
		//return to idle after player death
		SetState(eEnemyState::Idle);

		//set idle attack to new time
		m_fAttackTime = m_pTimer->GetTime();
	}
}

void CEnemy::SetState(eEnemyState state) {
	m_eEnemyState = state;
}

void CEnemy::simulate() {
	//Call base simulate
	CObject::simulate();
	
	//Finite state machine for dictating which manages the enemies state
	switch (m_eEnemyState) {
	case eEnemyState::Idle:
		//Enemy Idle State
		HandleIdle();
		HandleWalk();
		HandleTransitions();
		break;
	case eEnemyState::Attack:
		//Enemy Attack State
		HandleAttack();
		HandleTransitions();
		break;
	case eEnemyState::Chase:
		//Enemy Chase State
		HandleChase();
		HandleWalk();
		HandleTransitions();
		break;
	case eEnemyState::Stun:
		//Enemy Stun State
		HandleStun();
		break;
	case eEnemyState::Dead:
		//Enemy Dead State
		break;
	}
}

