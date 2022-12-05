#include "AbilitiesUI.h"
#include "UIHelpers.h"
#include "../../Player.h"
#include "../../ObjectManager.h"
#include "../../Common.h"

void AbilitiesUI::Draw()
{

	if (m_pPlayer == nullptr)
	{
		return;
	}
	//Get the deltaTime
	const float dt = m_pTimer->GetFrameTime();


	// Draw the UI element
	float windowWidth = m_pCanvas->m_nWidth;
	float windowHeight = m_pCanvas->m_nHeight;

	float x = windowWidth - 96;
	float y = 72;
	//Ability 1
	DrawAbility(Vector2(x, y), eSprite::Ability_Health);
	DrawAbility(Vector2(x, y + 82), eSprite::Ability_Health);
	DrawAbility(Vector2(x + 41, y + 41), eSprite::Ability_Health);
	DrawAbility(Vector2(x - 41, y + 41), eSprite::Ability_Health);
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
	
		if (m_pPlayer->getDisplayBlood() > m_pPlayer->bloodHealCost) {
			ability.m_f4Tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			ability.m_f4Tint = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
		}
	}

	UIHelpers::DrawSprite(ability, pos);
	UIHelpers::DrawAlignedText(text.c_str(), pos + Vector2(0.0f, -20.5f), HorizontalAlignment::Center, VerticalAlignment::Center, Colors::White);
}