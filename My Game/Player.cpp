/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "Helpers.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "Objects/Enemy.h"
#include "Utility/GameCamera.h"
#include "Utility/CMouse.h"



/// <summary>
/// Construct the player at a given position
/// </summary>
CPlayer::CPlayer(const Vector2& p) : Actor(p) {
	m_bIsTarget = true;
	m_bStatic = false;
	//Set the angle to 0 so carmilla isn't just standing there
	m_fRoll = 0.0;
	m_vBounds = Vector3(32.0f, m_pRenderer->GetHeight(eSprite::Player_Idle), 0.0f);

	m_fImageSpeed = 60 * 0.50f;
} //constructor

CPlayer::~CPlayer()
{

}

int CPlayer::getPlayerHealth() {
	return m_iHealth;
}

//reduce health by damage
//override from actor
void CPlayer::TakeDamage(int damage) {
	printf("player health: %d\n", m_iHealth);
	m_iHealth -= damage;
	m_tTimeSinceDamaged.SetTimeSince(0.0f);

	//if health is less than 0 mark as dead
	if (m_iHealth <= 0) {
		m_bDead = true;
	}
}

void CPlayer::HandleWalk() {

	if (m_vInput.x != 0.0f) {
		if (m_vInput.x > 0.0f) {
			SetSprite(eSprite::Player_Walk_Right);
		}

		if (m_vInput.x < 0.0f) {
			SetSprite(eSprite::Player_Walk_Left);
		}
	}

	if (m_vInput.x == 0.0f) {
		SetSprite(eSprite::Player_Idle);
	}

	m_vVelocity = m_vInput * m_fMoveSpeed;
}


//handles the dash state of the player
void CPlayer::HandleDash() {

	m_vVelocity = inputAtStateTransition * m_fDashSpeed;

	//check if a a quarter has passed, if so swap states, and set cooldown
	if ((m_tTimeSinceDash.GetTimeSince()) > 0.25f) {
		printf("end dash\n");
		coolDownReady = false;
		m_ePlayerState = ePlayerState::Idle;
	}

}

void CPlayer::HandleIdleTransitions() {
	//This is where you would hande transitions into attack, dash, death, stun, and the like
}

void CPlayer::simulate() {
	//Call base simulate
	CObject::simulate();

	UpdateDisplayHealth();

	//Switch statement for the player state
	/*
	The basic gist for how this is going to work is various simulations will be performed based on the value
	of m_ePlayerState. Long story short, you will perform your relevant logic.
	*/
	switch (m_ePlayerState) {
	case ePlayerState::Idle:
		//Player Idle State
		HandleWalk();
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
	case ePlayerState::Dead:
		//Player Dead State
		m_iHealth = 0;
		//call gameover eventually
		//reload the game
		break;

	}

}

void CPlayer::UpdateDisplayHealth() {
	const float t = m_pTimer->GetFrameTime(); //frame time
	m_fdisplayHealth = Lerp(m_fdisplayHealth, (float)m_iHealth, t * 5.0f);

	if (m_tTimeSinceDamaged.GetTimeSince() > 1.0f) {
		m_fDisplayLastHealth = Lerp(m_fDisplayLastHealth, m_fdisplayHealth, t * 3.0f);
	}
}

float CPlayer::getDisplayHealth() {
	return m_fdisplayHealth;
}

float CPlayer::getDisplayLastHealth() {
	return m_fDisplayLastHealth;
}

void CPlayer::HandleAttack() {
	//Declare a Vector2 called start at the current position of the player
	Vector2 start = this->GetPos() + inputAtStateTransition * 20.0f;

	//Declare a Vector2 called end at the current position of the player plus their input
	Vector2 end = start + inputAtStateTransition * 100.0f;

	//Print the input at the state transition
	printf("input at state transition: %f, %f\n", inputAtStateTransition.x, inputAtStateTransition.y);

	//Declare a pointer to an array of CObjects
	std::vector<CObject*> pObjects;


	pObjects = m_pObjectManager->IntersectLine(start, end);

	m_pCamera->Shake(0.25f, Vector2(5.0f, 5.0f));

	//Iterate over pObjects and draw a line to each one
	for (auto pObject : pObjects) {
		if (dynamic_cast<CEnemy*>(pObject) != nullptr) {
			printf("hit enemy\n");

			//make all enemies hit take damage
			//50 is test number, PLS switch once a sword damage amount is decided
			dynamic_cast<CEnemy*>(pObject)->TakeDamage(50);
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
	CObject::CollisionResponse(norm, d, pObj);
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
	//and set input
	if (m_pKeyboard->TriggerDown(' ') && coolDownReady && m_ePlayerState != ePlayerState::Dash) {
		timeAtDashStart = m_pTimer->GetTime();
		m_tTimeSinceDash.SetTimeSince(0.0f);

		if (horizontal != 0 || vertical != 0) {
			inputAtStateTransition = Vector2(horizontal, vertical);
		}
		else {
			inputAtStateTransition = Vector2(1.0, 0.0);
		}

		m_ePlayerState = ePlayerState::Dash;
	}

	//if it's in cooldown, check if cooldown should end
	if (!coolDownReady) {
		if ((m_tTimeSinceDash.GetTimeSince()) > 1.0f) {
			coolDownReady = true;
		}
	}

	if (m_pMouse->TriggerPressed(eMouseButton::Left) && CanAttack()) {

		if (horizontal != 0 || vertical != 0) {
			inputAtStateTransition = Vector2(horizontal, vertical);
		}
		else {
			inputAtStateTransition = Vector2(1.0, 0.0);
		}

		m_ePlayerState = ePlayerState::Attack;
	}


	Vector2 mousePosition = m_pMouse->Position;
	

	//Set the m_vInput vector to our horizontal and vertical values
	m_vInput.x = horizontal;
	m_vInput.y = vertical;

	//Flips the sprite based on the horizontal movement
	if (horizontal != 0.0f) {

	}

	//Normalize the vector
	m_vInput.Normalize();

}
