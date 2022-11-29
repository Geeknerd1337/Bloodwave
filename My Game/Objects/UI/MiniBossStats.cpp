#include "MiniBossStats.h"
#include "UIHelpers.h"
#include "../MiniBoss.h"
#include "../../ObjectManager.h"


void MiniBossStats::Draw() {
	const float t = m_pTimer->GetTime();
	//show bars if game is running
	if (m_pObjectManager->gameStatus) {
		DrawHealthBar();
	}
	
}

void MiniBossStats::DrawHealthBar() {
	//Draws the Mini Boss' health bar
	CObject* d = m_pObjectManager->GetMiniBoss();

	CMiniBoss* m_pMiniBoss = (CMiniBoss*)d;

	if (m_pMiniBoss != nullptr) {
		float x = (1280.0f / 5.0f) - 30.0f;
		float y = 600.0f;
		float w = 832.0f;
		float h = 25.0f;

		UIHelpers::DrawRectangle(Vector2(x, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.5));
		std::string hp = "HP";
		std::string name = "Baron Zintius";
		UIHelpers::DrawAlignedText(hp.c_str(), Vector2(x, y + h / 2.0f + 3.0f), HorizontalAlignment::Left, VerticalAlignment::Center, Colors::White);
		UIHelpers::DrawAlignedText(name.c_str(), Vector2(x, y + h / 2.0f + 3.0f), HorizontalAlignment::Left, VerticalAlignment::Top, Colors::BlueViolet);
		float vertStatPadding = 10.0f;
		Vector2 pos = Vector2(x + 35.0f, y + vertStatPadding / 2.0f);
		Vector2 size = Vector2(315.0f, h - vertStatPadding);
		UIHelpers::DrawRectangle(Vector2(x + 50.0, y + vertStatPadding / 2.0f), Vector2(w - 60, h - vertStatPadding), Vector4(108.0 / 255.0, 35.0 / 255.0, 48.0 / 255.0, 1.0));
		UIHelpers::DrawStatBar(pos, size, m_pMiniBoss->GetDisplayLastHealth(), 100.0f, Vector4(255 / 255.0, 235 / 255.0f, 87 / 255.0f, 1.0f));
		UIHelpers::DrawStatBar(pos, size, m_pMiniBoss->GetDisplayHealth(), 100.0f, Vector4(190.0/255.0, 39.0/255.0, 67.0/255.0, 1.0));
	}
	
}