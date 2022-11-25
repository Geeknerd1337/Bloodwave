/// \file Enemy.h
/// \brief Interface for the enemy object class CEnemy.

#ifndef __L4RC_GAME_ENEMY_H__
#define __L4RC_GAME_ENEMY_H__

#include "Actor.h"
#include "../Player.h"
#include "../Utility/TimeSince.h"
#include "../ObjectManager.h"

/// \brief The enemy object. 
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
    
    TimeSince m_tTimeSinceStunned;
    Vector2 m_vstunDirection;
    float m_fStunSpeed = 800.0f;
    float m_fStunTime = 0.25f;
    
    //float for attack time
    float m_fAttackTime = 0.0f;

    Vector2 idleVelocity = Vector2(0, 0);
    
    //holds random number to determine idle velocity
    float randomNumber = 0.0;
    
    //enemy chase and attack radii
    float enemyChaseRadius = 30.0;
    float enemyAttackRadius = 30.0;

    //idle and chase speeds
    float m_fIdleSpeed = 10.0f;
    float m_fChaseSpeed = 100.0f;

    //attack damage
    int m_iAttackPoints = 10;

    //vector between enemy and player
    Vector2 vEnemyToPlayer = Vector2(300, 300);

    /// <summary>
    /// Idle state for enemy
    /// </summary>
    void HandleIdle();

    /// <summary>
    /// Chase state for enemy
    /// </summary>
    virtual void HandleChase(); 

    /// <summary>
    /// Handles the logic for enemy walk animations
    /// </summary>
    virtual void PlayWalkAnimation();

    /// <summary>
    /// Attack state for enemy
    /// </summary>
    virtual void HandleAttack();

    /// <summary>
    /// Executes the transitions into different enemy states
    /// </summary>
    virtual void HandleTransitions();

    /// <summary>
    /// Stun state for enemy
    /// </summary>
    virtual void HandleStun();

	Vector2 m_vPushVelocity = Vector2(0, 0);

    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

public:
	
    CEnemy(const Vector2& p); ///< Constructor.
    ~CEnemy();

    virtual void drawBegin() override;
	
    virtual void buildInput() override;

	virtual void simulate() override;

    virtual void TakeDamage(int damage) override;

    void SetState(eEnemyState);

   virtual void DeathFX();

}; //CEnemy

#endif //__L4RC_GAME_ENEMY_H__
