#pragma once
#include "Enemy.h"

class CSpitterEnemy :
    public CEnemy
{
protected:
    virtual void HandleStun() override;

public:
    CSpitterEnemy(const Vector2& p);
    ~CSpitterEnemy();
};

