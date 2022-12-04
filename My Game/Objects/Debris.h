#pragma once
#include "../Object.h"
#include "../Utility/TimeSince.h"
#include "Component.h"
#include "../Common.h"

class Debris : public CObject, public LComponent{
public:
	float z = 1.0f;
	float gravity = 300.0f;
	float m_fRollSpeed = 0.0f;
	bool m_bFade = true;
	Vector3 velocity;
	Debris(const Vector2& p, eSprite spr);

	virtual void drawBegin() override;
	virtual void draw() override;
	virtual void simulate() override;
	

	//Destroy
	virtual void destroy();

	TimeSince m_tTimeSinceLanded;

	void SetRandomVelocity();
	
};