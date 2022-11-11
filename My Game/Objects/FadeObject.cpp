#include "FadeObject.h"

FadeObject::FadeObject(const Vector2& p, eSprite spr) : CObject(spr, p) {
	m_tTimeSinceCreated.SetTimeSince(0.0f);
	m_fDuration = 0.0f;
	
}

void FadeObject::Initialize(float duration, eSprite spr, int frameNum, int depth, float roll) {
	m_fDuration = duration;
	m_fImageSpeed = 0.0f;
	m_nSpriteIndex = (UINT)spr;
	m_nCurrentFrame = frameNum;
	m_iDepth = depth;
	m_fRoll = roll;
}

void FadeObject::simulate() {
	//Base
	CObject::simulate();

	//If the time since created is greater than the duration
	if (m_tTimeSinceCreated.GetTimeSince() > m_fDuration) {
		//Mark as dead
		m_bDead = true;
	}

	printf("HMMM");

	m_fAlpha = 1.0f - (m_tTimeSinceCreated.GetTimeSince() / m_fDuration);
}