#pragma once
#include <vector>
#include "../../Common.h"
#include "UIElement.h"


class Canvas : public CCommon {
	public:
		//Vector of UI elements
		std::vector<UIElement*> UIElements;
		void AddElement(UIElement* element);
		void Draw();
	
};