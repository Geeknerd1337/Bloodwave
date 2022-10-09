/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "Helpers.h"


/// Create and initialize an player object given its initial position.
/// \param p Initial position of player.

CPlayer::CPlayer(const Vector2& p) : Actor(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so carmella isn't just standing there
	m_fRoll = 0.0;
} //constructor


//This is where we will do the majority of our work
void CPlayer::move() {
	const float t = m_pTimer->GetFrameTime(); //time
	const Vector2 view = GetViewVector(); //view vector
	//TODO: Replace this with generic speed value
	m_vPos += 200.0f * t * m_vInput;
	
	//TODO: Remove
	if (m_vInput.x != 0.0f) {
		if (m_vInput.x > 0.0f) {
			printf("Setting Sprite Player Right\n");
			SetSprite(eSprite::Player_Idle_Right);
		}

		if (m_vInput.x < 0.0f){
			printf("Setting Sprite Player Left\n");
			SetSprite(eSprite::Player_Idle_Left);
		}
	}

} //move

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