#pragma once
#include "Debris.h"

class BloodParticle : public Debris
{
public:
	
	BloodParticle(const Vector2& p, eSprite spr);
	
	virtual void simulate() override;
	virtual void land() override;
	virtual void drawBegin() override;
	
};