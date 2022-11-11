#pragma once
#include "../Object.h"
#include "../Utility/TimeSince.h"
class FadeObject : public CObject {
public:
	FadeObject(const Vector2& p, eSprite spr);

	void Initialize(float duration, eSprite spr, int frameNum, int depth, float roll);
	
	virtual void simulate() override;
private:
	TimeSince m_tTimeSinceCreated;
	float m_fDuration;
	
};