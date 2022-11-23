#include "WaveUI.h"
#include "../../Utility/WaveManager.h"
#include "UIHelpers.h"
#include "../../Helpers.h"
#include "../../Utility/TimeSince.h"

WaveUI::WaveUI() {
	float windowWidth = m_pCanvas->m_nWidth;
	float windowHeight = m_pCanvas->m_nHeight;

	timerY = windowHeight + 64.0f;
}

void WaveUI::Draw() {
	const float t = m_pTimer->GetFrameTime();

	float windowWidth = m_pCanvas->m_nWidth;
	float windowHeight = m_pCanvas->m_nHeight;

	float w = 175.0f;
	float h = 48.0f;
	float x = (windowWidth / 2.0f) - w/2.0f;
	float y = windowHeight - h;
	

	if (m_pWaveManager->m_iCurrentWave != 0) {
		UIHelpers::DrawRectangle(Vector2(x, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.25));
		std::string waveText = "WAVE " + std::to_string(m_pWaveManager->m_iCurrentWave);
		UIHelpers::DrawAlignedText(waveText.c_str(), Vector2(x + w / 2.0f, y + h / 2.0f), HorizontalAlignment::Center, VerticalAlignment::Center, Colors::White);
	}


	if (m_pWaveManager->m_iCurrentWave == 0) {
		timerY = Lerp(timerY, y, 10.0f * t);
	}
	else {
		timerY = Lerp(timerY, y - 48.0f, 10.0f * t);
	}

	if (m_pWaveManager->m_bWaveStarted) {
		timerY = Lerp(timerY, windowHeight + 86.0f, 10.0f * t);

		enemiesX = Lerp(enemiesX, x, 8.0f * t);
	}
	else {
		enemiesX = Lerp(enemiesX, -200.0f, 8.0f * t);
	}

	
	UIHelpers::DrawRectangle(Vector2(x, timerY), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.25));
	//A string which takes timeSinceWave and converts it to a string
	float seconds = m_pWaveManager->m_fTimeBetweenWaves - m_pWaveManager->m_tTimeSinceLastWave.GetTimeSince();
	int secondsInt = (int)seconds;
	std::string timeSinceWave = std::to_string(secondsInt);
	UIHelpers::DrawAlignedText(timeSinceWave.c_str(), Vector2(x + w / 2.0f, timerY + h / 2.0f), HorizontalAlignment::Center, VerticalAlignment::Center, Colors::White);
	

	y -= 48.0f;
	//Enemies Remaining
	UIHelpers::DrawRectangle(Vector2(enemiesX, y), Vector2(w, h), Vector4(0.0, 0.0, 0.0, 0.25));
	std::string waveText = "Enemies: " + std::to_string(m_pWaveManager->EnemyCount());
	UIHelpers::DrawAlignedText(waveText.c_str(), Vector2(enemiesX + w / 2.0f, y + h / 2.0f), HorizontalAlignment::Center, VerticalAlignment::Center, Colors::White);
}