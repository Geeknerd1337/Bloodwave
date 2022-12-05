#pragma once
#include "../Object.h"
#include "../Utility/TimeSince.h"
#include "Component.h"
#include "../Common.h"

class MeleeSwipe : public CObject, public LComponent {
public:
	virtual void ImageLooped(eSprite) override;
	MeleeSwipe(const Vector2& p, eSprite spr);
	
	virtual void simulate() override;

	TimeSince TimeSinceSpawned;
};