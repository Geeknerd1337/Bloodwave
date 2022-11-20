#include "Acid.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "../Player.h"

void CAcid::CollisionResponse(const Vector2&, float, CObject* pObj)
{
	if (dynamic_cast<CPlayer*>(pObj) == m_pPlayer) {
		m_pPlayer->TakeDamage(m_iDamage);
	}

	
}

void CAcid::DeathFX()
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

CAcid::CAcid(eSprite t, const Vector2& p) : CObject(t, p) {
	m_bIsBullet = true;
	m_bStatic = false;
	m_bIsTarget = false;
} //constructor

CAcid::~CAcid()
{
}
