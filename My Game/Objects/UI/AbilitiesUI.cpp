#include "AbilitiesUI.h"
#include "UIHelpers.h"
#include "../../Player.h"
#include "../../ObjectManager.h"
#include "../../Common.h"

void AbilitiesUI::Draw()
{
	// Draw the UI element
	float windowWidth = m_pCanvas->m_nWidth;
	float windowHeight = m_pCanvas->m_nHeight;

	float x = windowWidth - 96;
	float y = 72;
	//Ability 1
	DrawAbility(Vector2(x, y));
	DrawAbility(Vector2(x, y + 82));
	DrawAbility(Vector2(x + 41, y + 41 ));
	DrawAbility(Vector2(x - 41, y + 41));
}

void AbilitiesUI::DrawAbility(Vector2 pos)
{
	LSpriteDesc2D spr;
	spr.m_nSpriteIndex = (UINT)eSprite::Diamond;
	spr.m_fAlpha = 0.5f;
	spr.m_fXScale = 1.0f;
	spr.m_fYScale = 1.0f;
	
	UIHelpers::DrawSprite(spr, pos);
}