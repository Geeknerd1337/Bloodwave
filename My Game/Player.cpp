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
#include "Objects/FadeObject.h"
#include "Particle.h"
#include "ParticleEngine.h"

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
	if (m_tiFrame.GetTimeSince() > 1.0f && shieldOn == false) {
		printf("player health: %d\n", m_iHealth);
		m_iHealth -= damage;
		m_tTimeSinceDamaged.SetTimeSince(0.0f);

		m_tiFrame.SetTimeSince(0.0f);

		m_pAudio->play(eSound::Hit);

		//if health is less than 0 mark as dead
		if (m_iHealth <= 0) {
			m_ePlayerState = ePlayerState::Dead;
		}
	}
}

void CPlayer::DeathScreen() {
	LParticleDesc2D d; //particle descriptor

	d.m_nSpriteIndex = (UINT)eSprite::Loose;
	d.m_vPos = Vector2(m_pCamera->m_cameraPos.x, m_pCamera->m_cameraPos.y);

	m_pParticleEngine->create(d);
}

void CPlayer::PlayAttackAnimation() {
	
	m_fImageSpeed = 60 * 0.20f;

	if (inputAtStateTransition.x != 0.0f) {
		if (inputAtStateTransition.x > 0.0) {
			SetSprite(eSprite::Player_Attack_Right);
		}
		if (inputAtStateTransition.x < 0.0) {
			SetSprite(eSprite::Player_Attack_Left);
		}
	}

	if (inputAtStateTransition.x == 0.0f) {
		SetSprite(eSprite::Player_Idle);
	}

	m_vVelocity = m_vInput * m_fMoveSpeed;
}

void CPlayer::PlayWalkAnimation() {

	m_fImageSpeed = 60 * 0.50f;

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
		coolDownReady = false;
		m_ePlayerState = ePlayerState::Idle;
	}

	if (m_tTimeSinceDashEffect.GetTimeSince() > 0.05f) {
		FadeObject* obj = (FadeObject*)m_pObjectManager->create(eSprite::Fade_Object, GetPos());
		obj->Initialize(1.0f,(eSprite)m_nSpriteIndex, m_nCurrentFrame, m_iDepth + 1, m_fRoll);
		obj->m_f4Tint = Vector4(0.0f, 0.8f, 1.0f, 0.5f);
		m_tTimeSinceDashEffect.SetTimeSince(0.0f);
	}

}

bool CPlayer::DashAvailable() {

	if (!coolDownReady) {
		return false;
	}

	if (m_ePlayerState == ePlayerState::Dash) {
		return false;
	}

	if (m_nStamina < m_nDashCost) {
		return false;
	}

	return true;
}

void CPlayer::StaminaDepletion(int i) {
	
	if (m_nStamina > 0) {
		m_nStamina -= i;
	}

	if (m_nStamina < 0) {
		m_nStamina = 0;
	}
}

void CPlayer::StaminaRegeneration() {
	
	if (m_tTimeSinceStaminaRegen.GetTimeSince() > 1.0f) {
	
		m_nStamina += 100;

		if (m_nStamina > 1000) {
			m_nStamina = 1000;
		}
		
		m_tTimeSinceStaminaRegen.SetTimeSince(0.0f);
	}
}

void CPlayer::HandleIdleTransitions() {
	//This is where you would hande transitions into attack, dash, death, stun, and the like
}

void CPlayer::simulate() {
	//Call base simulate
	CObject::simulate();

	UpdateDisplayHealth();
	UpdateDisplayStamina();
	UpdateDisplayBlood();
	
	StaminaRegeneration();

	//tint based on abilities
	if (shieldOn) {
		m_f4Tint = Vector4(0.5, 0, 0.8, 1);
	}
	else if (statBuffOn) {
		m_f4Tint = Vector4(0, 0.8, 0, 1);
	}
	else {
		m_f4Tint = Vector4(1, 1, 1, 1);
	}


	if (m_nBlood > 0 && m_tTimeSinceLastAttack.GetTimeSince() > 1.0f) {
		m_nBlood -= 100.0f * m_pTimer->GetFrameTime();
	}

	//Switch statement for the player state
	/*
	The basic gist for how this is going to work is various simulations will be performed based on the value
	of m_ePlayerState. Long story short, you will perform your relevant logic.
	*/
	switch (m_ePlayerState) {
	case ePlayerState::Idle:
		//Player Idle State
		PlayWalkAnimation();
		HandleIdleTransitions();
		break;
	case ePlayerState::Attack:
		//Player Attack State
		PlayAttackAnimation();
		HandleAttack();
		break;
	case ePlayerState::Dash:
		//Player Dash State
		HandleDash();
		break;
	case ePlayerState::Dead:
		//Player Dead State
		//reload the game
		
		//player pointer is dead
		m_bDead = true;
		//set it to false since game ended
		m_pObjectManager->gameStatus = false;
		DeathScreen();
		m_pAudio->play(eSound::GameOver);
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

void CPlayer::UpdateDisplayStamina() {
	const float t = m_pTimer->GetFrameTime(); //frame time
	m_fdisplayStamina = Lerp(m_fdisplayStamina, (float)m_nStamina, t * 10.0f);
	
	if (m_tTimeSinceStaminaUsed.GetTimeSince() > 1.0f) {
		m_fDisplayLastStamina = Lerp(m_fDisplayLastStamina, m_fdisplayStamina, t * 10.0f);
	}

}

void CPlayer::UpdateDisplayBlood() 
	{
		const float t = m_pTimer->GetFrameTime(); //frame time
		m_fdisplayBlood = Lerp(m_fdisplayBlood, (float)m_nBlood, t * 10.0f);

		if (m_tTimeSinceBloodUsed.GetTimeSince() > 1.0f) {
			m_fDisplayLastBlood = Lerp(m_fDisplayLastBlood, m_fdisplayBlood, t * 10.0f);
		}
	}


void CPlayer::BloodBeam()
{
}



float CPlayer::getDisplayHealth() {
	return m_fdisplayHealth;
}

float CPlayer::getDisplayLastHealth() {
	return m_fDisplayLastHealth;
}

float CPlayer::getDisplayStamina() {
	return m_fdisplayStamina;
}

float CPlayer::getDisplayLastStamina() {
	return m_fDisplayLastStamina;
}

float CPlayer::getDisplayBlood() {
	return m_fdisplayBlood;
}

float CPlayer::getDisplayLastBlood() {
	return m_fDisplayLastBlood;
}

void CPlayer::HandleAttack() {
	//Declare a Vector2 called start at the current position of the player
	Vector2 start = this->GetPos() + inputAtStateTransition * 20.0f;

	//Declare a Vector2 called end at the current position of the player plus their input
	Vector2 end = start + inputAtStateTransition * 100.0f;
	
	//Declare a pointer to an array of CObjects
	std::vector<CObject*> pObjects;

	pObjects = m_pObjectManager->IntersectLine(start, end);

	//Iterate over pObjects and draw a line to each one
	for (auto pObject : pObjects) {
		if (dynamic_cast<CEnemy*>(pObject) != nullptr) {

			//make all enemies hit take damage
			dynamic_cast<CEnemy*>(pObject)->TakeDamage(m_iAttackPoints);
			
			//shake cam once enemies take damange
			m_pCamera->Shake(0.25f, Vector2(2.0f, 2.0f));

			m_nBlood += 50.0f;
			m_tTimeSinceLastAttack.SetTimeSince(0.0f);

			if (m_nBlood > 1000.0f) {
				m_nBlood = 1000.0f;
			}
			
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

	//invert showInfo when I is pressed
	if (m_pKeyboard->TriggerDown('I')) {
		if (showInfo) {
			showInfo = false;
		}
		else {
			showInfo = true;
		}
	}

	//dash trigger
	//and set input
	if (m_pKeyboard->TriggerDown(' ') && DashAvailable()) {
		timeAtDashStart = m_pTimer->GetTime();
		m_tTimeSinceDash.SetTimeSince(0.0f);
		m_tTimeSinceDashEffect.SetTimeSince(0.0f);

		StaminaDepletion(m_nDashCost);

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

	//stat buff blood ability
	if (m_pKeyboard->TriggerDown('1') && m_nBlood > bloodStatBuffCost) {
		statBuffOn = true;
		m_tStatBuff.SetTimeSince(0.0f);

		m_nBlood -= bloodStatBuffCost;

		//buff stats
		m_iAttackPoints = 55;
		m_fMoveSpeed = 300.0f;
		m_nDashCost = 150.0f;

		m_pAudio->play(eSound::PowerUp);
	}

	//end stat buff
	if (statBuffOn && m_tStatBuff.GetTimeSince() > 5.0f) {
		statBuffOn = false;

		//set stats to normal
		m_iAttackPoints = 40;
		m_fMoveSpeed = 200.0f;
		m_nDashCost = 250.0f;
	}

	//invincibility shield blood ability
	if (m_pKeyboard->TriggerDown('2') && m_nBlood > bloodShieldCost) {
		shieldOn = true;
		m_tiShield.SetTimeSince(0.0f);

		m_nBlood -= bloodShieldCost;

		m_pAudio->play(eSound::PowerUp);
	}

	//end shield
	if (shieldOn && m_tiShield.GetTimeSince() > 5.0f) {
		shieldOn = false;
	}

	//blood beam ability
	//fire a shockwave beam that damages enemies in right or left direction
	if (m_pKeyboard->TriggerDown('3') && m_nBlood > bloodBeamCost) {
		m_nBlood -= bloodBeamCost;
		if (m_vVelocity.x < 0) {
			m_pObjectManager->FireBeam(this, eSprite::Bullet, true);
		}
		else {
			m_pObjectManager->FireBeam(this, eSprite::Bullet, false);
		}

		m_pAudio->play(eSound::PowerUp);
	}

	//blood heal ability
	if (m_pKeyboard->TriggerDown('4') && m_nBlood > bloodHealCost) {
		m_nBlood -= bloodHealCost;

		m_iHealth += bloodHealAmount;

		//make sure health can't be over 100
		if (m_iHealth > 100) {
			m_iHealth = 100;
		}

		m_pAudio->play(eSound::PowerUp);
	}

	if (m_pMouse->TriggerDown(eMouseButton::Left) && CanAttack()) {

		Vector2 mousePos = m_pMouse->GetMouseWorldPos();
		Vector2 playerPos = m_pPlayer->GetPos();

		Vector2 mouseDir = mousePos - playerPos;
		mouseDir.Normalize();

		//Round the x and y components of the mouse dir
		mouseDir.x = round(mouseDir.x);
		mouseDir.y = round(mouseDir.y);

		mouseDir.Normalize();

		inputAtStateTransition = mouseDir;

		m_ePlayerState = ePlayerState::Attack;
	}


	Vector2 mousePosition = m_pMouse->Position;
	

	//Set the m_vInput vector to our horizontal and vertical values
	m_vInput.x = horizontal;
	m_vInput.y = vertical;

	//Normalize the vector
	m_vInput.Normalize();

}


void CPlayer::drawBegin() {
	LSpriteDesc2D spr;
	spr.m_nSpriteIndex = (UINT)eSprite::Small_Circle;
	spr.m_f4Tint = Vector4(0.05f, 0.05f, 0.05f, 1.0f);
	spr.m_fAlpha = 0.25f;
	spr.m_vPos = GetPos() + Vector2(0.0f, -40.0f);
	spr.m_fXScale = 2.0f;
	spr.m_fYScale = 0.25f;
	
	m_pRenderer->Draw(&spr);
}