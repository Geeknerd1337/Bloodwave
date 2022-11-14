#include "BloodWaveRenderer.h"
#include "Helpers.h"

BloodWaveRenderer::BloodWaveRenderer(eSpriteMode eMode) : LSpriteRenderer(eMode)
{
}

void BloodWaveRenderer::DrawAlignedText(const char* text, const Vector2& pos, HorizontalAlignment hor, VerticalAlignment ver, XMVECTORF32 color)
{
	wchar_t* buffer = nullptr;
	MakeWideFileName(text, buffer);
	DrawAlignedText(buffer, pos, hor, ver, color);
	delete[] buffer;
}

void BloodWaveRenderer::DrawAlignedText(const wchar_t* text, const Vector2& pos, HorizontalAlignment hor, VerticalAlignment ver, XMVECTORF32 color)
{
	if (m_pFont == nullptr) {
		return;
	}

	Vector2 finalPos = pos;

	const RECT bounds = m_pFont->MeasureDrawBounds(text, XMFLOAT2(0.f, 0.f));
	const float width = (float)(bounds.right - bounds.left);
	const float height = (float)(bounds.bottom - bounds.top);

	

	
	///Switch case for the horizontal aligment which draws it
	switch (hor)
	{
	case HorizontalAlignment::Left:

		break;
	case HorizontalAlignment::Center:
		finalPos.x -= width / 2.0f;
		break;
	case HorizontalAlignment::Right:
		finalPos.x -= width;
		break;
	}
	
	//Same for vertical
	switch (ver)
	{
	case VerticalAlignment::Top:
		finalPos.y += height;
		break;
	case VerticalAlignment::Center:
		finalPos.y -= height / 2.0f;
		break;
	case VerticalAlignment::Bottom:
		finalPos.y -= height;
		break;
	}

	m_pFont->DrawString(m_pSpriteBatch.get(), text, finalPos, color);
	
	
}