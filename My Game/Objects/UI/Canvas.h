#pragma once
#include <vector>
#include "../../Common.h"
#include "UIElement.h"


class Canvas : public CCommon {
	public:
		Canvas(Vector2 size);
		std::vector<UIElement*> UIElements;
		void AddElement(UIElement* element);
		void Draw();
		int m_nWidth;
		int m_nHeight;
	private:
		
};