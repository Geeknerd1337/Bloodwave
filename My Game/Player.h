/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Objects/Actor.h"
#include "Timer.h"


/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CPlayer : public Actor {
protected:
	/// <summary>
	/// Timer which tells whether the player can dash or not
	/// </summary>
	float timeAtDashStart = 0.0f;
	bool setVelocity = true;
	bool coolDownReady = true;

	int stamina = 1000;

	/// <summary>
	/// Our run speed
	/// </summary>
	float m_fRunSpeed = 200.0f;

	/// <summary>
	/// The dash speed
	/// </summary>
	float m_fDashSpeed = 800.0f;

	/// <summary>
	/// Sometimes we need to capture input when transitioning into a state
	/// like the dash or the attack. This allows us to capture the input at that moment.
	/// </summary>
	Vector2 inputAtStateTransition = Vector2(0, 0);

	virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

	/// <summary>
	/// Handles the logic for the idle state
	/// </summary>
	void HandleIdle();

	/// <summary>
	/// Boolean representing whether or not the player can currently attack
	/// </summary>
	/// <returns></returns>
	bool CanAttack();

	/// <summary>
	/// Allows us to handle the attack state.
	/// </summary>
	void HandleAttack();

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
	~CPlayer();



	//Implement BuildInput
	virtual void buildInput() override;

	//Implement simulate
	virtual void simulate() override;




	//

}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H___