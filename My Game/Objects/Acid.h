#pragma once

#include "../Object.h"

class CAcid : public CObject {
protected:
	virtual void CollisionResponse(const Vector2&, float,
		CObject* = nullptr); ///< Collision response.
	virtual void DeathFX(); ///< Death special effects.

public:
	CAcid(eSprite t, const Vector2& p);
	~CAcid();

};