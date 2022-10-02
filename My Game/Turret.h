/// \file Turret.h
/// \brief Interface for the turret object class CTurret.

#ifndef __L4RC_GAME_TURRET_H__
#define __L4RC_GAME_TURRET_H__

#include "Object.h"

/// \brief The turret object. 
///
/// CTurret is the abstract representation of a turret object.

class CTurret: public CObject{
  protected:
    void RotateTowards(const Vector2&); ///< Swivel towards position.
    virtual void CollisionResponse(const Vector2&, float,
      CObject* = nullptr); ///< Collision response.
  
  public:
    CTurret(const Vector2& p); ///< Constructor.
    virtual void move(); ///< Move turret.
}; //CBullet

#endif //__L4RC_GAME_TURRET_H__