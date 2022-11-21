#ifndef __L4RC_GAME_MINIBOSS_H__
#define __L4RC_GAME_MINIBOSS_H__

#include "Enemy.h"
#include "Timer.h"
#include "../Utility/TimeSince.h"


class CMiniBoss : public CEnemy {
protected:

    //Display Health
    float m_fDisplayHealth = 250.0f;
    float m_fDisplayLastHealth = 250.0f;

    //Timing elements
    TimeSince m_tTimeSinceDamaged;
    TimeSince m_tiFrame;

    /// <summary>
    /// Stun state for enemy
    /// </summary>
    virtual void HandleStun();

    /// <summary>
    /// Updates the health that we use for a display using a lerp so that we can 
    /// smoothly show this value transitioning in the healthbar
    /// </summary>
    void UpdateDisplayHealth();

public:
	CMiniBoss(const Vector2& p);
    ~CMiniBoss();

    float GetDisplayHealth();
    float GetDisplayLastHealth();

    virtual void simulate() override;

    virtual void TakeDamage(int damage) override;

};
#endif