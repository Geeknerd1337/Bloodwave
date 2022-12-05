#pragma once
#include "../Object.h"
#include "../Utility/TimeSince.h"
#include "Component.h"
#include "../Common.h"

class BloodPool : public CObject, public LComponent {
public:
	TimeSince m_tTimeSinceSpawn;
	virtual void simulate() override;
	virtual void drawBegin() override;
	virtual void draw() override;
	void initialize();

	BloodPool(eSprite, const Vector2&);
};
