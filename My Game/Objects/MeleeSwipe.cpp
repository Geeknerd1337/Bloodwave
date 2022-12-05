#include "MeleeSwipe.h"
#include "../Helpers.h"

MeleeSwipe::MeleeSwipe(const Vector2& p, eSprite spr) : CObject(spr, p) {
	m_fImageSpeed = 2.5f;
	TimeSinceSpawned.SetTimeSince(0.0f);
}

void MeleeSwipe::ImageLooped(eSprite spr) {
	//m_bDead = true;
}

void MeleeSwipe::simulate() {
	//Call base
	CObject::simulate();
	float time = ((1 / 60.0f) * m_fImageSpeed) * 3.0f;
	if (TimeSinceSpawned.GetTimeSince() > time) {
		m_bDead = true;
	}
}