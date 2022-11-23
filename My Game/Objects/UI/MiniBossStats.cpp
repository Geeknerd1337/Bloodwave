#include "MiniBossStats.h"
#include "UIHelpers.h"
#include "../MiniBoss.h"
#include "../../ObjectManager.h"


void MiniBossStats::Draw() {
	const float t = m_pTimer->GetTime();
	DrawHealthBar();
}

void MiniBossStats::DrawHealthBar() {
	//Draws the Mini Boss' health bar
	CObject* d = m_pObjectManager->GetMiniBoss();

	CMiniBoss* m_pMiniBoss = (CMiniBoss*)d;

	if (m_pMiniBoss != nullptr) {
		float x = 115.0f;
		float y = 10.0f;
		float w = 360.0f;
		float h = 35.0f;
		UIHelpers::DrawRectangle(Vector2(x, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.5));
		std::string hp = "HP";
		UIHelpers::DrawAlignedText(hp.c_str(), Vector2(x, y + h / 2.0f + 3.0f), HorizontalAlignment::Left, VerticalAlignment::Center, Colors::White);
		float vertStatPadding = 10.0f;
		Vector2 pos = Vector2(x + 35.0f, y + vertStatPadding / 2.0f);
		Vector2 size = Vector2(315.0f, h - vertStatPadding);
		UIHelpers::DrawRectangle(pos, size, Vector4(30 / 255.0, 111 / 255.0f, 80 / 255.0f, 1.0f));
		UIHelpers::DrawStatBar(pos, size, m_pMiniBoss->GetDisplayLastHealth(), 100.0f, Vector4(255 / 255.0, 235 / 255.0f, 87 / 255.0f, 1.0f));
		UIHelpers::DrawStatBar(pos, size, m_pMiniBoss->GetDisplayHealth(), 100.0f, Vector4(90 / 255.0, 197 / 255.0f, 79 / 255.0f, 1.0f));
	}
	
}