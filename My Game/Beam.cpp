#include "Beam.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "ObjectManager.h"
#include "Common.h"
#include "Objects/Enemy.h"

void CBeam::CollisionResponse(const Vector2&, float, CObject* pObj)
{
		if (dynamic_cast<CEnemy*>(pObj) != nullptr) {

			//make enemy hit take damage
			dynamic_cast<CEnemy*>(pObj)->TakeDamage(m_iDamage);
		}
}

void CBeam::DeathFX()
{
	LParticleDesc2D d; //particle descriptor

	d.m_nSpriteIndex = (UINT)eSprite::Smoke;
	d.m_vPos = m_vPos;
	d.m_fLifeSpan = 0.5f;
	d.m_fMaxScale = 0.5f;
	d.m_fScaleInFrac = 0.2f;
	d.m_fFadeOutFrac = 0.8f;
	d.m_fScaleOutFrac = d.m_fFadeOutFrac;

	m_pParticleEngine->create(d); //create particle
}

CBeam::CBeam(eSprite t, const Vector2& p) : CObject(t, p)
{
	m_bIsBullet = true;
	m_bStatic = false;
	m_bIsTarget = false;
	printf("beam");

	killTimer.SetTimeSince(0.0f);
}

void CBeam::simulate() {
	m_iDepth = (int)m_vPos.y;
	UpdateFramenumber();

	if (killTimer.GetTimeSince() > 1.0f) {
		m_bDead = true;
		DeathFX();
	}
}
