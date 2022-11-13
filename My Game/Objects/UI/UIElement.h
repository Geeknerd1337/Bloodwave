#pragma once
#include "../../Common.h"
#include "ComponentIncludes.h"
#include "Component.h"
class UIElement : public CCommon, public LComponent {
public: 
	virtual void Draw();
};