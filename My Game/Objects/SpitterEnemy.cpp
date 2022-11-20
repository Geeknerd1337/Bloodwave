#include "SpitterEnemy.h"
#include <cmath>

CSpitterEnemy::CSpitterEnemy(const Vector2& p) : CEnemy(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so enemy is standing upright
	m_fRoll = 0.0;

	m_fRadius = 200.0f;
	//starts in idle state, so set it to slow idle speed
	m_fMoveSpeed = 15.0f;

	SetSprite(eSprite::SpitterEnemy_Idle);

	m_f4Tint = Vector4(0.5, 0, 0.5, 1);

	m_fImageSpeed = 60 * 0.50f;
} //constructor

CSpitterEnemy::~CSpitterEnemy()
{
}


void CSpitterEnemy::HandleStun() {
	if (m_tTimeSinceStunned.GetTimeSince() < m_fStunTime) {
		m_vVelocity = m_vstunDirection * m_fStunSpeed;

		//Get the sin using m_ptimer
		float sin = std::sin(m_pTimer->GetTime() * 100.0f);

		if (sin > 0) {
			//Set the image tint to red
			m_f4Tint = Vector4(1.0, 0.0, 0.0, 1.0);
		}
		else {
			m_f4Tint = Vector4(0.5, 0.0, 0.5, 1.0);
		}
	}
	else {
		SetState(eEnemyState::Idle);
		m_f4Tint = Vector4(0.5, 0.0, 0.5, 1.0);
	}
}