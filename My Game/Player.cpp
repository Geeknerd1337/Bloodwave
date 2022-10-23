/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "Helpers.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "Objects/Enemy.h"


/// <summary>
/// Construct the player at a given position
/// </summary>
CPlayer::CPlayer(const Vector2& p) : Actor(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so carmilla isn't just standing there
	m_fRoll = 0.0;
	m_vBounds = Vector3(32.0f, m_pRenderer->GetHeight(eSprite::Player_Idle), 0.0f);

	//Sortened timer for dash - feels punchier
	m_pDashEvent = new LEventTimer(0.8f);

} //constructor

CPlayer::~CPlayer()
{
	delete m_pCanDashEvent;
	delete m_pDashEvent;
}

void CPlayer::HandleIdle() {

	if (m_vInput.x != 0.0f) {
		if (m_vInput.x > 0.0f) {
			SetSprite(eSprite::Player_Idle_Right);
		}

		if (m_vInput.x < 0.0f) {
			SetSprite(eSprite::Player_Idle_Left);
		}
	}

	m_vVelocity = m_vInput * m_fMoveSpeed;
}

//handles the dash state of the player
void CPlayer::HandleDash() {


	//dashing speed
	m_fMoveSpeed = m_fDashSpeed;
	printf("in dash");

	//use bool setVelocity to set the velocity equal to what it is when you start the dash
	//currently velocity is manually set becasue the dash state starts upon game load
	if (setVelocity) {
		//changed m_vVelocity to m_vInput - this was causing the PC to teleport
		printf("set velocity");
		inputAtStateTransition = m_vInput;
		setVelocity = false;
	}

	//check if a second has passed, if so set the speed back, and swap states
	if (m_pDashEvent && m_pDashEvent->Triggered()) {
		m_fMoveSpeed = m_fRunSpeed;
		printf("end dash\n");
		setVelocity = true;

		//will prolly need to detect which state we should go to
		//and switch to that
		//but for now, we swap into idle at the end of a dash
		m_ePlayerState = ePlayerState::Idle;
	}

	m_vVelocity = inputAtStateTransition * m_fMoveSpeed;
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
		HandleAttack();
		break;
	case ePlayerState::Dash:
		//Player Dash State
		HandleDash();
		break;
	case ePlayerState::Stun:
		//Player Stun State
		break;
	case ePlayerState::Dead:
		//Player Dead State
		m_iHealth = 0;
		//call gameover eventually
		//reload the game
		break;

	}

}

void CPlayer::HandleAttack() {
	//Declare a Vector2 called start at the current position of the player
	Vector2 start = this->GetPos();

	//Declare a Vector2 called end at the current position of the player plus their input
	Vector2 end = start + inputAtStateTransition * 200.0f;

	//Declare a pointer to an array of CObjects
	std::vector<CObject*> pObjects;

	pObjects = m_pObjectManager->IntersectLine(start, end);

	//Iterate over pObjects and draw a line to each one
	for (auto pObject : pObjects) {
		if (dynamic_cast<CEnemy*>(pObject) != nullptr) {
			printf("hit enemy\n");
		}
	}

	m_ePlayerState = ePlayerState::Idle;
}

bool CPlayer::CanAttack() {
	return true;
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

	//dash trigger
	if (m_pKeyboard->TriggerDown(' ')) {
		m_ePlayerState = ePlayerState::Dash;
	}

	if (m_pKeyboard->TriggerDown('E') && CanAttack()) {

		if (horizontal != 0 || vertical != 0) {
			inputAtStateTransition = Vector2(horizontal, vertical);
		}
		else {
			inputAtStateTransition = Vector2(1.0, 0.0);
		}

		m_ePlayerState = ePlayerState::Attack;
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
