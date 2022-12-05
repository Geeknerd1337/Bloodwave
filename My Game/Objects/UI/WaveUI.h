#pragma once

#include "UIElement.h"


class WaveUI : public UIElement
{
public:
	virtual void Draw() override;
	float timerY = 0.0f;
	float enemiesX = 0.0f;

	//Constructor
	WaveUI();
};