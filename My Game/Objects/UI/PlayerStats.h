#pragma once

#include "UIElement.h"



class PlayerStats : public UIElement
{
public:
	virtual void Draw() override;
	void DrawHealthBar();
	void DrawStaminaBar();
	void DrawBloodBar();
	void InfoText();
};