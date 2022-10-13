/// \file Enemy.h
/// \brief Interface for the enemy object class CEnemy.

#ifndef __L4RC_GAME_ENEMY_H__
#define __L4RC_GAME_ENEMY_H__

#include "Actor.h"

/// \brief The player object. 
///
/// The abstract representation of the enemy object.

class CEnemy : public Actor {
protected:
    bool m_bStrafeLeft = false; ///< Strafe left.
    bool m_bStrafeRight = false; ///< Strafe right.
    bool m_bStrafeBack = false; ///< Strafe back.



    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

public:
	
    CEnemy(const Vector2& p); ///< Constructor.

    /// <summary>
    /// Gets the position of he enemy
    /// </summary>
    const Vector2& GetPos() const;
	
    virtual void buildInput() override;

	virtual void simulate() override;

}; //CEnemy

#endif //__L4RC_GAME_ENEMY_H__
