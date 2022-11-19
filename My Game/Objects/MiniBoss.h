#ifndef __L4RC_GAME_MINIBOSS_H__
#define __L4RC_GAME_MINIBOSS_H__

#include "Enemy.h"


class CMiniBoss : public CEnemy {
protected:
	int m_iAttackPoints = 25;
    int m_iHealth = 250;

    /// <summary>
    /// Chase state for enemy
    /// </summary>
    //virtual void HandleChase();

    /// <summary>
    /// Handles the logic for enemy walk animations
    /// </summary>
    //virtual void HandleWalk();

    /// <summary>
    /// Attack state for enemy
    /// </summary>
    virtual void HandleAttack();

    /// <summary>
    /// Executes the transitions into different enemy states
    /// </summary>
    //virtual void HandleTransitions();

    /// <summary>
    /// Stun state for enemy
    /// </summary>
    //virtual void HandleStun();

public:
	CMiniBoss(const Vector2& p);
	~CMiniBoss();

    virtual void simulate() override;

    
};
#endif