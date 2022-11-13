#include "PlayerStats.h"
#include "UIHelpers.h"
#include "../../Player.h"


void PlayerStats::Draw()
{
	const float t = m_pTimer->GetTime();
	
	//Get a width that is 100 + sin(t)
	float width = 100.0f + sin(t * 5.0f) * 50.0f;

	
	UIHelpers::DrawRectangle(Vector2(0.0, 100.0), Vector2(width, 50.0), Vector4(1.0, 0.0, 0.0, 1.0)); 
	
	//Draws the players health bar
	float x = 10.0f;
	float y = 115.0f;
	float w = 360.0f;
	float h = 35.0f;
	UIHelpers::DrawRectangle(Vector2(x, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.5));
	std::string hp = "HP";
	UIHelpers::DrawAlignedText(hp.c_str(), Vector2(x, y + h/2.0f + 3.0f), HorizontalAlignment::Left, VerticalAlignment::Center, Colors::White);
	float vertStatPadding = 10.0f;
	Vector2 pos = Vector2(x + 35.0f, y + vertStatPadding / 2.0f);
	Vector2 size = Vector2(315.0f, h - vertStatPadding);
	UIHelpers::DrawRectangle(pos, size, Vector4(30 / 255.0, 111 / 255.0f, 80 / 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayLastHealth(), 100.0f, Vector4(255 / 255.0, 235 / 255.0f, 87/ 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayHealth(), 100.0f, Vector4(90 / 255.0, 197 / 255.0f, 79 / 255.0f, 1.0f));
}