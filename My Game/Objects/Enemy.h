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

    //float for idle time
    float m_fIdleTime = 0.0f;
    Vector2 idleVelocity = Vector2(0, 0);
    //holds random number to determine idle velocity
    float randomNumber;
    float enemyChaseRadius = 250.0;
    float enemyAttackRadius;

    //idle and chase speeds
    float m_fIdleSpeed = 10.0f;
    float m_fChaseSpeed = 100.0f;

    //vector between enemy and player
    Vector2 vEnemyToPlayer = Vector2(300, 300);

    //function for idle state
    void handleIdle();

    //function for chase state
    void handleChase();

    //function for attack state
    void handleAttack();

    void handleTransitions();


    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

public:
	
    CEnemy(const Vector2& p); ///< Constructor.
    ~CEnemy();


	
    virtual void buildInput() override;

	virtual void simulate() override;

    virtual void TakeDamage(int damage) override;

}; //CEnemy

#endif //__L4RC_GAME_ENEMY_H__
