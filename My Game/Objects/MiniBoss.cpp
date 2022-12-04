/// \file MiniBoss.cpp
/// \brief Code for the mini boss object class CMiniBoss

#include "MiniBoss.h"
#include "../../My Game/Helpers.h"
#include <cmath>

CMiniBoss::CMiniBoss(const Vector2& p) : CEnemy(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	
	//Set the angle to 0 so mini boss is standing upright
	m_fRoll = 0.0;

	m_fRadius = 200.0f;
	
	//starts in idle state, so set it to slow idle speed
	m_fMoveSpeed = 10.0f;

	SetSprite(eSprite::Mini_Boss_Idle);

	//set sprite size
	m_fXScale = 1.5f;
	m_fYScale = 1.5f;

	//R, G, B, A tint
	m_f4Tint = Vector4(0.5, 0.0, 1.0, 0.0);

	m_iAttackPoints = 25;
	m_iHealth = 250;
	m_fStunSpeed = 500.0f;
	m_fStunTime = 0.10f;
	m_fChaseSpeed = 150.0f;

	m_fImageSpeed = 60 * 0.50f;
}

CMiniBoss::~CMiniBoss() {}

void CMiniBoss::TakeDamage(int damage) {
	if (m_tiFrame.GetTimeSince() > 1.0f) {
		m_iHealth -= damage;

		//Get the direction to the player
		Vector2 dir = (m_pPlayer->m_vPos - m_vPos);
		dir.Normalize();
		m_vstunDirection = dir * -1.0f;

		m_tTimeSinceStunned.SetTimeSince(0.0f);

		SetState(eEnemyState::Stun);

		m_tTimeSinceDamaged.SetTimeSince(0.0f);

		m_tiFrame.SetTimeSince(0.0f);

		//if health is less than 0 mark as dead
		if (m_iHealth <= 0) {
			m_bDead = true;
			m_f4Tint = Vector4(0.5, 0.0, 1.0, 0.0);
			DeathFX();
		}
	}
}

//setting tint to purple, and tuned stun time and speed to less overall
void CMiniBoss::HandleStun() {
	if (m_tTimeSinceStunned.GetTimeSince() < m_fStunTime) {
		m_vVelocity = m_vstunDirection * m_fStunSpeed;

		//Get the sin using m_ptimer
		float sin = std::sin(m_pTimer->GetTime() * 100.0f);

		if (sin > 0) {
			//Set the image tint to red
			m_f4Tint = Vector4(1.0, 0.0, 0.0, 1.0);
		}
		else {
			m_f4Tint = Vector4(0.5, 0.0, 1.0, 0.0);
		}
	}
	else {
		SetState(eEnemyState::Idle);
		m_f4Tint = Vector4(0.5, 0.0, 1.0, 0.0);
	}
}

float CMiniBoss::GetDisplayHealth() {
	return m_fDisplayHealth;
}

float CMiniBoss::GetDisplayLastHealth() {
	return m_fDisplayLastHealth;
}

//Update display health
void CMiniBoss::UpdateDisplayHealth() {
	const float t = m_pTimer->GetFrameTime(); //frame time
	m_fDisplayHealth = Lerp(m_fDisplayHealth, (float)m_iHealth, t * 5.0f);

	if (m_tTimeSinceDamaged.GetTimeSince() > 1.0f) {
		m_fDisplayLastHealth = Lerp(m_fDisplayLastHealth, m_fDisplayHealth, t * 3.0f);
	}
}

void CMiniBoss::simulate() {
	
	//Call base simulate
	CObject::simulate();

	UpdateDisplayHealth();

	m_vPushVelocity = m_vPushVelocity * 0.9f;

	//Finite state machine for dictating which manages the MB's state
	switch (m_eEnemyState) {
	case eEnemyState::Idle:
		//Enemy Idle State
		HandleIdle();
		PlayWalkAnimation();
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
		PlayWalkAnimation();
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