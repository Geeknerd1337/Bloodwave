#include "PlayerStats.h"
#include "UIHelpers.h"
#include "../../Player.h"
#include "../../ObjectManager.h"
#include "../../Common.h"


void PlayerStats::Draw()
{
	if (m_pObjectManager->gameStatus) {
		const float t = m_pTimer->GetTime();
		DrawHealthBar();
		DrawStaminaBar();
		DrawBloodBar();
	}
}

void PlayerStats::DrawHealthBar() {
	//Draws the players health bar
	float x = 10.0f;
	float y = 115.0f;
	float w = 360.0f;
	float h = 35.0f;
	UIHelpers::DrawRectangle(Vector2(x, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.5));
	std::string hp = "HP";
	UIHelpers::DrawAlignedText(hp.c_str(), Vector2(x, y + h / 2.0f + 3.0f), HorizontalAlignment::Left, VerticalAlignment::Center, Colors::White);
	float vertStatPadding = 10.0f;
	Vector2 pos = Vector2(x + 35.0f, y + vertStatPadding / 2.0f);
	Vector2 size = Vector2(315.0f, h - vertStatPadding);
	UIHelpers::DrawRectangle(pos, size, Vector4(30 / 255.0, 111 / 255.0f, 80 / 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayLastHealth(), 100.0f, Vector4(255 / 255.0, 235 / 255.0f, 87 / 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayHealth(), 100.0f, Vector4(90 / 255.0, 197 / 255.0f, 79 / 255.0f, 1.0f));
}

void PlayerStats::DrawStaminaBar(){
	//Draws the players stamina bar
	float x = 10.0f;
	float y = 75.0;
	float w = 360.0f;
	float h = 35.0f;
	UIHelpers::DrawRectangle(Vector2(x, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.5));
	std::string stam = "ST";
	UIHelpers::DrawAlignedText(stam.c_str(), Vector2(x, y + h / 2.0f + 3.0f), HorizontalAlignment::Left, VerticalAlignment::Center, Colors::White);
	float vertStatPadding = 10.0f;
	Vector2 pos = Vector2(x + 35.0f, y + vertStatPadding / 2.0f);
	Vector2 size = Vector2(315.0f, h - vertStatPadding);
	UIHelpers::DrawRectangle(pos, size, Vector4(0 / 255.0, 105/ 255.0f,	170 / 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayLastStamina(), 1000.0f, Vector4(255 / 255.0, 235 / 255.0f, 87 / 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayStamina(), 1000.0f, Vector4(12 / 255.0, 241 / 255.0f, 255 / 255.0f, 1.0f));
}

void PlayerStats::DrawBloodBar() {
	//Draws the players blood bar
	float x = 10.0f;
	float y =35.0f;
	float w = 360.0f;
	float h = 35.0f;
	UIHelpers::DrawRectangle(Vector2(x, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.5));
	std::string blood = "BL";
	UIHelpers::DrawAlignedText(blood.c_str(), Vector2(x, y + h / 2.0f + 3.0f), HorizontalAlignment::Left, VerticalAlignment::Center, Colors::White);
	float vertStatPadding = 10.0f;
	Vector2 pos = Vector2(x + 35.0f, y + vertStatPadding / 2.0f);
	Vector2 size = Vector2(315.0f, h - vertStatPadding);
	UIHelpers::DrawRectangle(pos, size, Vector4(87 / 255.0, 28 / 255.0f, 39/ 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayLastBlood(), 1000.0f, Vector4(255 / 255.0, 235 / 255.0f, 87 / 255.0f, 1.0f));
	UIHelpers::DrawStatBar(pos, size, m_pPlayer->getDisplayBlood(), 1000.0f, Vector4(245 / 255.0, 85 / 255.0f, 93 / 255.0f, 1.0f));
}
