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
	bool m_bLanded = false;
	
	Vector3 velocity;
	Debris(const Vector2& p, eSprite spr);

	virtual void drawBegin() override;
	virtual void draw() override;
	virtual void simulate() override;
	

	/// <summary>
	/// Method which gets called when debris is destroyed
	/// </summary>
	virtual void destroy();

	/// <summary>
	/// Method which gets called when the debris lands on the ground
	/// </summary>
	virtual void land();

	TimeSince m_tTimeSinceLanded;

	void SetRandomVelocity();
	
};