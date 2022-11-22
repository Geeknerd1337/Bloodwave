#pragma once
#include "Object.h"
#include "Utility/TimeSince.h"

class CBeam :
    public CObject
{
protected:
    virtual void CollisionResponse(const Vector2&, float,
        CObject* = nullptr); ///< Collision response.
    virtual void DeathFX(); ///< Death special effects.

    //damage it does
    int m_iDamage = 100;

    //timer to check if we should kill beam object
    TimeSince killTimer;

public:
    CBeam(eSprite t, const Vector2& p); ///< Constructor.

    virtual void simulate()override;
};

