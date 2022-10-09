#include "../Object.h"

#ifndef __L4RC_ACTOR_PLAYER_H__
#define __L4RC_ACTOR_PLAYER_H__

class Actor : public CObject {
protected:
	//Vector 2 called input
	Vector2 m_vInput = Vector2(0, 0); ///< Input vector.
	
	//Health
	
	
public:
	Actor(const Vector2& p); ///< Constructor.
};

#endif