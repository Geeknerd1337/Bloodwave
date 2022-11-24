#pragma once

#include "../Object.h"
#include "../Utility/TimeSince.h"

//acid object for spitter enemy attack
class CAcid : public CObject {
protected:
	//collision response to make player take damage
	virtual void CollisionResponse(const Vector2&, float,
		CObject* = nullptr); 

	virtual void DeathFX(); ///< Death special effects.

	//damage it does
	int m_iDamage = 20;

	float scale = 1.0f;

	//timer to check if we should kill acid object
	TimeSince killTimer;


public:
	//constructor and destructor
	CAcid(eSprite t, const Vector2& p);
	~CAcid();

	//simulate overrided so we can check if acid object has been spawned in for 2 seconds
	virtual void simulate() override;
};