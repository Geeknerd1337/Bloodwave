/// \file Bullet.h
/// \brief Interface for the bullet object class CBullet.

#ifndef __L4RC_GAME_BULLET_H__
#define __L4RC_GAME_BULLET_H__

#include "Object.h"

/// \brief The bullet object. 
///
/// The abstract representation of a bullet object. Bullet objects die when
/// they collide with anything and emit a cloud of smoke for anything except
/// an ant.

class CBullet: public CObject{
  protected:
    virtual void CollisionResponse(const Vector2&, float,
      CObject* = nullptr); ///< Collision response.
    virtual void DeathFX(); ///< Death special effects.

  public:
    CBullet(eSprite t, const Vector2& p); ///< Constructor.
}; //CBullet

#endif //__L4RC_GAME_BULLET_H__