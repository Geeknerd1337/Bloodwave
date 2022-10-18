/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Objects/Actor.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CPlayer : public Actor {
protected:
	bool m_bStrafeLeft = false; ///< Strafe left.
	bool m_bStrafeRight = false; ///< Strafe right.
	bool m_bStrafeBack = false; ///< Strafe back.

	//timer to tell if dash should end yet
	LEventTimer* m_pDashEvent = nullptr;
	bool setVelocity = true;
	Vector2 inputAtDashStart = Vector2(0, 0);

	virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.
	
	/// <summary>
	/// Handles the logic for the idle state
	/// </summary>
	void HandleIdle();

	/// <summary>
	/// Handles the logic for the dash state
	/// </summary>
	void HandleDash();

	/// <summary>
	/// Handles the logic for transitioning into other states from the idle state.
	/// </summary>
	void HandleIdleTransitions();
	
	/// <summary>
	/// The current state of the player
	/// </summary>
	ePlayerState m_ePlayerState = ePlayerState::Idle; 

public:
	CPlayer(const Vector2& p); ///< Constructor.

	const Vector2& GetPos() const; ///< Get position.

	//Implement BuildInput
	virtual void buildInput() override;

	//Implement simulate
	virtual void simulate() override;


	
	
	//

}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__