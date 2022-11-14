#ifndef __L4RC_GAME_MINIBOSS_H__
#define __L4RC_GAME_MINIBOSS_H__

#include "Enemy.h"


class CMiniBoss : public CEnemy {
protected:

public:
	CMiniBoss(const Vector2& p);
	~CMiniBoss();

};
#endif