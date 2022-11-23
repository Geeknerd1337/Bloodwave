#include "Canvas.h"
#include "PlayerStats.h"
#include "WaveUI.h"
#include "MiniBossStats.h"

Canvas::Canvas(Vector2 size)
{
	m_nWidth = size.x;
	m_nHeight = size.y;
}

void Canvas::AddElement(UIElement* element)
{
	UIElements.push_back(element);
}

void Canvas::Initialize()
{
	AddElement(new PlayerStats());
	AddElement(new WaveUI());
	AddElement(new MiniBossStats());
}

Canvas::~Canvas()
{
	//Free every UI element in the UIElements vector
	for (int i = 0; i < UIElements.size(); i++)
	{
		delete UIElements[i];
	}
}

void Canvas::Draw()
{
	//Iterate over elements and draw them
	for (int i = 0; i < UIElements.size(); i++)
	{
		if (UIElements[i] != nullptr)
		{
			UIElements[i]->Draw();
		}
	}
}