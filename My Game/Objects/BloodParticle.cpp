#include "BloodParticle.h"
#include "../Helpers.h"
#include "BloodPool.h"
#include "../Common.h"
#include "../ObjectManager.h"

BloodParticle::BloodParticle(const Vector2& p, eSprite spr) : Debris(p, spr) {
	SetRandomVelocity();
	gravity = 600.0f;
}

void BloodParticle::simulate() {
	//Base
	Debris::simulate();
	//Point in the direction of the x component of our velocity and our z 
	m_fRoll = atan2(-velocity.x, velocity.z) + 90.0f;
}


void BloodParticle::land() {
	CObject* obj = m_pObjectManager->createDirect(new BloodPool(eSprite::Blood_Pool,m_vPos));
	((BloodPool*)obj)->initialize();
	m_bDead = true;
}

void BloodParticle::drawBegin() {
		LSpriteDesc2D desc;
		desc.m_nSpriteIndex = (UINT)eSprite::Small_Circle;
		desc.m_vPos = m_vPos;
		desc.m_fXScale = 0.5f;
		desc.m_fYScale = 0.5f;
		desc.m_f4Tint = Vector4(0.05f, 0.05f, 0.05f, 1.0f);
		desc.m_fAlpha = 0.1f * m_fAlpha;
		

		m_pRenderer->Draw(&desc);

}