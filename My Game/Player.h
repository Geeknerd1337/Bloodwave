/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Objects/Actor.h"
#include "Timer.h"
#include "Utility/TimeSince.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CPlayer : public Actor {
protected:
	/// <summary>
	/// Time when you start dashing to decide if dash if over
	/// cool down to decide if you can dash
	/// </summary>
	float timeAtDashStart = 0.0f;
	bool coolDownReady = true;

	int stamina = 1000;

	/// <summary>
	/// Our run speed
	/// </summary>
	float m_fRunSpeed = 200.0f;

	float m_fdisplayHealth = 100.0f;
	float m_fDisplayLastHealth = 100.0f;

	/// <summary>
	/// The dash speed
	/// </summary>
	float m_fDashSpeed = 800.0f;

	Vector2 m_vMouseDirection;

	/// <summary>
	/// Sometimes we need to capture input when transitioning into a state
	/// like the dash or the attack. This allows us to capture the input at that moment.
	/// </summary>
	Vector2 inputAtStateTransition = Vector2(0, 0);

	virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

	/// <summary>
	/// Handles the logic for the walk animations
	/// </summary>
	void HandleWalk();

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

	TimeSince m_tTimeSinceDash;
	TimeSince m_tTimeSinceDashEffect;
	TimeSince m_tTimeSinceDamaged;

	/// <summary>
	/// Handles the logic for transitioning into other states from the idle state.
	/// </summary>
	void HandleIdleTransitions();

	/// <summary>
	/// Updates the health that we use for a display using a lerp so that we can smoothly show this value transitioning in the healthbar
	/// </summary>
	void UpdateDisplayHealth();

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

	/// <summary>
	/// Overridden TakeDamage function from actor to simulate player taking damage and death
	/// </summary>
	/// <param name="damage"></param>
	virtual void TakeDamage(int damage) override;

	/// <summary>
	/// Get player health
	/// </summary>
	/// <returns></returns>
	int getPlayerHealth();

	

	/// <summary>
	/// Returns the players display health
	/// </summary>
	float getDisplayHealth();

	float getDisplayLastHealth();

}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H___