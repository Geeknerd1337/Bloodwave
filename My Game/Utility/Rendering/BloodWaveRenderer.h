#pragma once
#include "SpriteDesc.h"
#include "SpriteRenderer.h"
#include "../../GameDefines.h"

class BloodWaveRenderer : public LSpriteRenderer
{
public:
	BloodWaveRenderer(eSpriteMode);

	void DrawAlignedText(const char*, const Vector2& pos, HorizontalAlignment hor, VerticalAlignment ver, XMVECTORF32 = Colors::Black);
	void DrawAlignedText(const wchar_t*, const Vector2& pos, HorizontalAlignment hor, VerticalAlignment ver, XMVECTORF32 = Colors::Black);
};
