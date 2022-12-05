#include "AbilitiesUI.h"
#include "UIHelpers.h"
#include "../../Player.h"
#include "../../ObjectManager.h"
#include "../../Common.h"
#include "../../Helpers.h"

void AbilitiesUI::Draw()
{

	if (m_pPlayer == nullptr)
	{
		return;
	}
	//Get the deltaTime
	const float dt = m_pTimer->GetFrameTime();

	if (m_pObjectManager->gameStatus) {
		// Draw the UI element
		float windowWidth = m_pCanvas->m_nWidth;
		float windowHeight = m_pCanvas->m_nHeight;

		float x = windowWidth - 96;
		float y = 72;
		//Ability 1
		DrawAbility(Vector2(x, y), eSprite::Ability_Buff);
		DrawAbility(Vector2(x, y + 82), eSprite::Ability_Health);
		DrawAbility(Vector2(x + 41, y + 41), eSprite::Ability_Shield);
		DrawAbility(Vector2(x - 41, y + 41), eSprite::Ability_Beam);
	}
	for (int i = 0; i < 4; i++) {
		//Lerp the 4 values of bump back down to 1
		bump[i] = Lerp(bump[i], 1.0f, dt * 5.0f);
	}
}

void AbilitiesUI::DrawAbility(Vector2 pos, eSprite abilitySpr)
{
	LSpriteDesc2D spr;
	spr.m_nSpriteIndex = (UINT)eSprite::Diamond;
	spr.m_fAlpha = 0.25f;
	spr.m_fXScale = 1.0f;
	spr.m_fYScale = 1.0f;

	UIHelpers::DrawSprite(spr, pos);
	std::string text = "-1";

	LSpriteDesc2D ability;
	ability.m_nSpriteIndex = (UINT)abilitySpr;


	//TODO: These should be their own clases but its almost 1am
	if ((UINT)abilitySpr == (UINT)eSprite::Ability_Health) {
		
		text = "4";
		ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		ability.m_fXScale = bump[3];
		ability.m_fYScale = bump[3];
	
		if (m_pPlayer->getDisplayBlood() > m_pPlayer->bloodHealCost) {
			if (!haveBumped[3]) {
				bump[3] = 1.5f;
				haveBumped[3] = true;
			}
			ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			ability.m_f4Tint = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			haveBumped[3] = false;
		}

		
	}

	if ((UINT)abilitySpr == (UINT)eSprite::Ability_Buff) {

		text = "1";
		ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		ability.m_fXScale = bump[0];
		ability.m_fYScale = bump[0];

		if (m_pPlayer->getDisplayBlood() > m_pPlayer->bloodStatBuffCost) {
			if (!haveBumped[0]) {
				bump[0] = 1.5f;
				haveBumped[0] = true;
			}
			ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			ability.m_f4Tint = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			haveBumped[0] = false;
		}

		
	}

	if ((UINT)abilitySpr == (UINT)eSprite::Ability_Shield) {

		text = "2";
		ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		ability.m_fXScale = bump[1];
		ability.m_fYScale = bump[1];

		if (m_pPlayer->getDisplayBlood() > m_pPlayer->bloodShieldCost) {
			if (!haveBumped[1]) {
				bump[1] = 1.5f;
				haveBumped[1] = true;
			}
			ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			ability.m_f4Tint = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			haveBumped[1] = false;
		}

		
	}

	if ((UINT)abilitySpr == (UINT)eSprite::Ability_Beam) {

		text = "3";
		ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		ability.m_fXScale = bump[2];
		ability.m_fYScale = bump[2];

		if (m_pPlayer->getDisplayBlood() > m_pPlayer->bloodBeamCost) {
			if (!haveBumped[2]) {
				bump[2] = 1.5f;
				haveBumped[2] = true;
			}
			ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			ability.m_f4Tint = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			haveBumped[2] = false;
		}

		
	}

	UIHelpers::DrawSprite(ability, pos);
	UIHelpers::DrawAlignedText(text.c_str(), pos + Vector2(0.0f, -25.0f), HorizontalAlignment::Center, VerticalAlignment::Center, Colors::White);
}