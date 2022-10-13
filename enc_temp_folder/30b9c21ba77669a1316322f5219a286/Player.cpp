/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "Helpers.h"


/// <summary>
/// Construct the player at a given position
/// </summary>
CPlayer::CPlayer(const Vector2& p) : Actor(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so carmilla isn't just standing there
	m_fRoll = 0.0;
} //constructor




void CPlayer::HandleIdle() {

	if (m_vInput.x != 0.0f) {
		if (m_vInput.x > 0.0f) {
			printf("Setting Sprite Player Right\n");
			SetSprite(eSprite::Player_Idle_Right);
		}

		if (m_vInput.x < 0.0f) {
			printf("Setting Sprite Player Left\n");
			SetSprite(eSprite::Player_Idle_Left);
		}
	}

	//Use print f to print a boolean
	printf("%d\n", instanceof<Actor>(this));

	m_vVelocity = m_vInput * m_fMoveSpeed;
}

void CPlayer::HandleIdleTransitions() {
	//This is where you would hande transitions into attack, dash, death, stun, and the like
}

void CPlayer::simulate() {
	//Switch statement for the player state
	/*
	The basic gist for how this is going to work is various simulations will be performed based on the value
	of m_ePlayerState. Long story short, you will perform your relevant logic.
	*/
	switch (m_ePlayerState) {
	case ePlayerState::Idle:
		//Player Idle State
		HandleIdle();
		HandleIdleTransitions();
		break;
	case ePlayerState::Attack:
		//Player Attack State
		break;
	case ePlayerState::Dash:
		//Player Dash State
		break;
	case ePlayerState::Stun:
		//Player Stun State
		break;
	case ePlayerState::Dead:
		//Player Dead State
		break;

	}

}



/// Response to collision. If the object being collided with is a bullet, then
/// play a sound, otherwise call `CObject::CollisionResponse` for the default
/// collision response.
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

void CPlayer::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {
	if (pObj && pObj->isBullet())
		m_pAudio->play(eSound::Grunt);

	else CObject::CollisionResponse(norm, d, pObj);
} //CollisionResponse

const Vector2& CPlayer::GetPos() const {
	return m_vPos;
} //GetPos

//Implement buildInput
void CPlayer::buildInput() {

	float vertical = 0.0f;
	if (m_pKeyboard->Down('W')) {

		vertical += 1.0f;
	}

	if (m_pKeyboard->Down('S')) {
		vertical -= 1.0f;
	}

	float horizontal = 0.0f;
	if (m_pKeyboard->Down('A')) {
		horizontal -= 1.0f;
	}

	if (m_pKeyboard->Down('D')) {
		horizontal += 1.0f;
	}

	//Set the m_vInput vector to our horizontal and vertical values
	m_vInput.x = horizontal;
	m_vInput.y = vertical;

	//Flips the sprite based on the horizontal movement
	if (horizontal != 0.0f) {

	}


	//Normalize the vector
	m_vInput.Normalize();

}