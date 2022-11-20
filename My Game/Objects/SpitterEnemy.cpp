#include "SpitterEnemy.h"
#include "ComponentIncludes.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include <cmath>
#include "Debris.h"

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
	m_iAttackPoints = 20;
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

void CSpitterEnemy::HandleAttack()
{
	//get player health
	int playerHealth = std::floor(m_pPlayer->getPlayerHealth());

	//attack every second
	if ((m_pTimer->GetTime() - m_fAttackTime) > 1.0f) {
		//if player health is > 0, attack
		if (playerHealth > 0) {
			m_pObjectManager->ThrowAcid(this, eSprite::Acid);
		}

		//return to idle after player death
		SetState(eEnemyState::Idle);

		//set idle attack to new time
		m_fAttackTime = m_pTimer->GetTime();
	}
}

//display death sprite and death effects
void CSpitterEnemy::DeathFX() {
	LParticleDesc2D d; //particle descriptor
	d.m_vPos = m_vPos; //center particle at turret center

	//set sprite and particle settings
	d.m_nSpriteIndex = (UINT)eSprite::SpitterEnemy_Dead;
	d.m_f4Tint = Vector4(0.5, 0, 0.5, 1);
	d.m_fLifeSpan = 2.0f;
	d.m_fMaxScale = 1.0f;
	d.m_fScaleInFrac = 0.0f;
	d.m_fFadeOutFrac = 0.8f;
	d.m_fScaleOutFrac = 0;
	m_pParticleEngine->create(d);

	CObject* torso = m_pObjectManager->createDirect(new Debris(m_vPos, eSprite::SpitterMonster_Gib));
	torso->m_f4Tint = Vector4(0.5, 0, 0.5, 1);

	((Debris*)torso)->SetRandomVelocity();
	torso->m_fRoll = 0.0f;
	//Set torso m_fRollSpeed to a random value between -100 and 100
	((Debris*)torso)->m_fRollSpeed = (rand() % 20) - 10.0f;

} //DeathFX