#include "PlayerStats.h"
#include "UIHelpers.h"


void PlayerStats::Draw()
{
	const float t = m_pTimer->GetTime();
	
	//Get a width that is 100 + sin(t)
	float width = 100.0f + sin(t * 5.0f) * 50.0f;

	
	UIHelpers::DrawRectangle(Vector2(0.0, 100.0), Vector2(width, 50.0), Vector4(1.0, 0.0, 0.0, 1.0));
	UIHelpers::DrawSprite(eSprite::Health_Pip, Vector2(0.0, 100.0));

	
	UIHelpers::DrawRectangle(Vector2(10.0, 115.0), Vector2(360.0, 35.0), Vector4(0.0, 0.0, 0.0, 0.5));
	std::string hp = "HP";
	m_pRenderer->DrawAlignedText(hp.c_str(), Vector2(10.0, 115.0), HorizontalAlignment::Center, VerticalAlignment::Center, Colors::White);
}