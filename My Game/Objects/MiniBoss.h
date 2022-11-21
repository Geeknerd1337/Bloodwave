#ifndef __L4RC_GAME_MINIBOSS_H__
#define __L4RC_GAME_MINIBOSS_H__

#include "Enemy.h"


class CMiniBoss : public CEnemy {
protected:

    /// <summary>
    /// Handles the logic for enemy walk animations
    /// </summary>
    //virtual void HandleWalk();

    /// <summary>
    /// Stun state for enemy
    /// </summary>
    virtual void HandleStun();

public:
	CMiniBoss(const Vector2& p);
    ~CMiniBoss();

};
#endif