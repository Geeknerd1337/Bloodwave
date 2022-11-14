#pragma once
#include "../Common.h"
#include "Component.h"
#include "TimeSince.h"

class WaveManager : public CCommon, public LComponent {
public:
	void Initialize();
	
	float m_fTimeBetweenWaves = 10.0f;
	TimeSince m_tTimeSinceLastWave;
	int m_iCurrentWave = 0;
	int m_iEnemiesPerWave = 10;
	
	void StartWave();
	int EnemyCount();
	void EndWave();
	void Simulate();

	bool m_bWaveStarted;
};