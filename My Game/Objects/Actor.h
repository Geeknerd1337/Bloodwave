#include "../Object.h"

#ifndef __L4RC_ACTOR_PLAYER_H__
#define __L4RC_ACTOR_PLAYER_H__

class Actor : public CObject {
protected:
	//Vector 2 called input
	Vector2 m_vInput = Vector2(0, 0); ///< Input vector.
	
	//Health
	int m_iHealth = 100; ///< Health of the actor.

	//Move Speed
	float m_fMoveSpeed = 200.0f; ///< Movement speed of the actor.

	
	
public:
	Actor(const Vector2& p); ///< Constructor.

};

#endif