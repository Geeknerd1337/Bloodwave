#include "SpitterEnemy.h"

CSpitterEnemy::CSpitterEnemy(const Vector2& p) : CEnemy(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so enemy is standing upright
	m_fRoll = 0.0;

	m_fRadius = 200.0f;
	//starts in idle state, so set it to slow idle speed
	m_fMoveSpeed = 15.0f;

	SetSprite(eSprite::Enemy_Idle);

	m_fImageSpeed = 60 * 0.50f;
} //constructor

CSpitterEnemy::~CSpitterEnemy()
{
}
