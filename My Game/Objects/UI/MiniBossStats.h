#pragma once

#include "UIElement.h"

class MiniBossStats : public UIElement {
public:
	virtual void Draw() override;
	void DrawHealthBar();
};
