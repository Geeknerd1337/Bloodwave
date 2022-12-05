#include "BloodPool.h"
#include "../Helpers.h"

BloodPool::BloodPool(eSprite spr, const Vector2& p) : CObject(spr, p) {
	m_tTimeSinceSpawn = 0.0f;

	//Set m_fRoll to a random value
	
}

void BloodPool::initialize() {
	m_fRoll = rand() % 360;
	m_fAlpha = 0.5f;
}

void BloodPool::simulate() {
	if (m_tTimeSinceSpawn.GetTimeSince() > 3.0f) {
		m_bDead = true;
	}

	//Lerp between 0.5 and 2.5 for m_fxscale and m_fyscale
	if (m_tTimeSinceSpawn.GetTimeSince() < 2.0f) {
		m_fXScale = Lerp(1.0f, 2.0f, m_tTimeSinceSpawn.GetTimeSince() / 2.0f);
		m_fYScale = Lerp(1.0f, 2.0f, m_tTimeSinceSpawn.GetTimeSince() / 2.0f);
	}
	else {
		m_fAlpha = Lerp(0.5f,0.0f,(m_tTimeSinceSpawn.GetTimeSince() - 2.0f) / 1.0f);
	}
}

void BloodPool::draw() {
	
}

void BloodPool::drawBegin() {
	LSpriteDesc2D desc;
	desc.m_nSpriteIndex = (UINT)eSprite::Blood_Pool;
	desc.m_vPos = m_vPos;
	desc.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	desc.m_fRoll = m_fRoll;
	desc.m_fXScale = m_fXScale;
	desc.m_fYScale = m_fYScale;
	desc.m_fAlpha = m_fAlpha;

	m_pRenderer->Draw(&desc);
}
