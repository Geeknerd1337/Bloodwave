#pragma once
#include "../../Common.h"
#include "Canvas.h"
#include "../../GameDefines.h"


class UIHelpers : public CCommon {
public:
	static Vector2 GetScreenPos();
	static void DrawStatBar(Vector2 pos, Vector2 size, float value, float maxValue, Vector4 color);
	static void DrawRectangle(Vector2 pos, Vector2 size, Vector4 color);
	static void DrawSprite(eSprite spr, Vector2 pos);
};