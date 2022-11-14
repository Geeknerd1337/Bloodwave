#include "Debris.h"
#include "../Helpers.h"

Debris::Debris(const Vector2& p, eSprite spr) : CObject(spr, p) {
}


void Debris::SetRandomVelocity() {
	Vector2 planar = m_pRandom->randv();
	planar.Normalize();
	//Multiply this by a value between 5 and 20 using srand()
	planar *= (rand() % 15) + 5.0f;
	
	float z = (rand() % 15) + 15.0f;

	velocity = Vector3(planar.x, planar.y, z) * 10.0f;	
}

void Debris::draw() {
	LSpriteDesc2D desc;
	desc.m_vPos = m_vPos;
	desc.m_vPos.y += z;
	desc.m_nSpriteIndex = m_nSpriteIndex;
	desc.m_nCurrentFrame = m_nCurrentFrame;
	desc.m_fRoll = m_fRoll;
	desc.m_fAlpha = m_fAlpha;
	
	m_iDepth = (int)desc.m_vPos.y - z;
	
	m_pRenderer->Draw(&desc);
}

void Debris::simulate() {
	const float dt = m_pTimer->GetFrameTime();

	z += velocity.z * dt;
	
	if (z > 0) {
		velocity.z -= gravity * dt;
		m_tTimeSinceLanded.SetTimeSince(0.0f);
	}
	else {
		z = 0;
	}

	if (z <= 0) {
		velocity.x = Lerp(velocity.x, 0.0f, dt * 5);
		velocity.y = Lerp(velocity.x, 0.0f, dt * 5);
		m_fRollSpeed = Lerp(m_fRollSpeed, 0.0f, dt * 2.0f);

		if (m_tTimeSinceLanded.GetTimeSince() > 1.0f) {
			m_fAlpha = 1.0f - ((m_tTimeSinceLanded.GetTimeSince() - 1.0f) / 2.0f);
		}

		if (m_fAlpha <= 0.0f) {
			m_bDead = true;
		}
	}


	m_fRoll += m_fRollSpeed * dt;

	//Update m_vPos
	m_vPos += Vector2(velocity.x,velocity.y) * dt;
	
}

void Debris::drawBegin() {
	LSpriteDesc2D desc;
	desc.m_nSpriteIndex = (UINT)eSprite::Small_Circle;
	desc.m_vPos = m_vPos;
	desc.m_f4Tint = Vector4(0.05f, 0.05f, 0.05f, 1.0f);
	desc.m_fAlpha = 0.25f * m_fAlpha;
	
	m_pRenderer->Draw(&desc);
}

