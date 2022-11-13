#include "UIHelpers.h"
#include "../../Utility/GameCamera.h"

Vector2 UIHelpers::GetScreenPos()
{
	Vector2 windowOffset = Vector2(m_pCanvas->m_nWidth / 2.0, m_pCanvas->m_nHeight / 2.0);
	Vector2 screenPos = m_pCamera->m_cameraPos - windowOffset;
	return screenPos;
}


void UIHelpers::DrawRectangle(Vector2 pos, Vector2 size, Vector4 color)
{
	float x1 = GetScreenPos().x + pos.x;
	float y1 = GetScreenPos().y + pos.y;
	float x2 = x1 + size.x;
	float y2 = y1 + size.y;

	LSpriteDesc2D spr;
	spr.m_nSpriteIndex = (UINT)eSprite::Single_Pixel;
	spr.m_vPos = Vector2(x1 + size.x / 2.0f, y1 + size.y / 2.0f);
	spr.m_fXScale = size.x;
	spr.m_fYScale = size.y;
	spr.m_f4Tint = color;
	
	m_pRenderer->Draw(&spr);

}

void UIHelpers::DrawSprite(eSprite spr, Vector2 pos)
{
	float x = GetScreenPos().x + pos.x;
	float y = GetScreenPos().y + pos.y;
	LSpriteDesc2D sprDesc;
	sprDesc.m_nSpriteIndex = (UINT)spr;
	sprDesc.m_vPos = Vector2(x,y);
	m_pRenderer->Draw(&sprDesc);
}