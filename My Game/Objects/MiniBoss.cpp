/// \file MiniBoss.cpp
/// \brief Code for the mini boss object class CMiniBoss

#include "MiniBoss.h"

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

	m_fImageSpeed = 60 * 0.50f;
}

CMiniBoss::~CMiniBoss() {}