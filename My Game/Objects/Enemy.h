/// \file Enemy.h
/// \brief Interface for the enemy object class CEnemy.

#ifndef __L4RC_GAME_ENEMY_H__
#define __L4RC_GAME_ENEMY_H__

#include "Actor.h"
#include "../Player.h"

/// \brief The player object. 
///
/// The abstract representation of the enemy object.

class CEnemy : public Actor {
protected:
	
    /// <summary>
    /// The current state of the enemy
    /// </summary>
    eEnemyState m_eEnemyState = eEnemyState::Idle;

    //timer for idle velocity
    LEventTimer* m_pIdleEvent = nullptr;
    Vector2 idleVelocity = Vector2(0, 0);
    //holds random number to determine idle velocity
    float randomNumber;
    float enemyChaseRadius = 250.0;
    float enemyAttackRadius;

    //function for idle state
    void handleIdle();

    //function for chase state
    void handleChase();

    void handleTransitions();


    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

public:
	
    CEnemy(const Vector2& p); ///< Constructor.
    ~CEnemy();


	
    virtual void buildInput() override;

	virtual void simulate() override;

}; //CEnemy

#endif //__L4RC_GAME_ENEMY_H__
