#pragma once

#include "UIElement.h"
#include "../../Utility/TimeSince.h"


class AbilitiesUI : public UIElement
{
private:
	
public:

	virtual void Draw() override;
	void DrawAbility(Vector2 pos, eSprite);
	//Array of 4 bump floats
	float bump[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
};