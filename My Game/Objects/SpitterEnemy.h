#pragma once
#include "Enemy.h"

//special enemy type that throws acid to do damage
class CSpitterEnemy :
    public CEnemy
{
protected:
    virtual void HandleStun() override;
    virtual void HandleAttack() override;


public:
    CSpitterEnemy(const Vector2& p);
    ~CSpitterEnemy();

    virtual void DeathFX() override;
};

