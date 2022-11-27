#pragma once

#include "UIElement.h"
#include "../../Utility/TimeSince.h"



class PlayerStats : public UIElement
{
private:
	TimeSince m_tiInfo;
public:

	virtual void Draw() override;
	void DrawHealthBar();
	void DrawStaminaBar();
	void DrawBloodBar();
	void InfoText();
	void IFadetext();
};