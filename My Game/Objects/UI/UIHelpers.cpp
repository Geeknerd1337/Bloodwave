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
	spr.m_fAlpha = color.w;
	
	m_pRenderer->Draw(&spr);

}

void UIHelpers::DrawStatBar(Vector2 pos, Vector2 size, float value, float maxValue, Vector4 color)
{
	DrawRectangle(pos, Vector2(size.x * (value/maxValue), size.y), color);
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

void UIHelpers::DrawSprite(LSpriteDesc2D spr, Vector2 pos)
{
	float x = GetScreenPos().x + pos.x;
	float y = GetScreenPos().y + pos.y;
	spr.m_vPos = Vector2(x, y);

	m_pRenderer->Draw(&spr);
}


void UIHelpers::DrawAlignedText(const char* text, Vector2 pos, HorizontalAlignment hAlign, VerticalAlignment vAlign, XMVECTORF32 color)
{
	float x = pos.x;
	float y = m_pCanvas->m_nHeight - pos.y;

	m_pRenderer->DrawAlignedText(text, Vector2(x, y), hAlign, vAlign, color);
}


void UIHelpers::DrawAlignedTextOutline(const char* text, Vector2 pos, HorizontalAlignment hAlign, VerticalAlignment vAlign, XMVECTORF32 color, XMVECTORF32 outLineColor)
{
	float x = pos.x;
	float y = m_pCanvas->m_nHeight - pos.y;

	
	
	//Draw outline using 8 calls to aligned text (bad)
	//In an ideal world I wouldn't be a lazy jerk and would go look to see what it takes to get SDF working for fonts
	//in directX but considering I'm being paid a grand total of nothing to do this, I'm gonna opt out
	m_pRenderer->DrawAlignedText(text, Vector2(x + 3.0f, y), hAlign, vAlign, outLineColor);
	m_pRenderer->DrawAlignedText(text, Vector2(x - 3.0f, y), hAlign, vAlign, outLineColor);
	m_pRenderer->DrawAlignedText(text, Vector2(x, y + 3.0f), hAlign, vAlign, outLineColor);
	m_pRenderer->DrawAlignedText(text, Vector2(x, y - 3.0f), hAlign, vAlign, outLineColor);
	m_pRenderer->DrawAlignedText(text, Vector2(x + 3.0f, y + 3.0f), hAlign, vAlign, outLineColor);
	m_pRenderer->DrawAlignedText(text, Vector2(x - 3.0f, y - 3.0f), hAlign, vAlign, outLineColor);
	m_pRenderer->DrawAlignedText(text, Vector2(x + 3.0f, y - 3.0f), hAlign, vAlign, outLineColor);
	m_pRenderer->DrawAlignedText(text, Vector2(x - 3.0f, y + 3.0f), hAlign, vAlign, outLineColor);
	
	m_pRenderer->DrawAlignedText(text, Vector2(x, y), hAlign, vAlign, color);
}