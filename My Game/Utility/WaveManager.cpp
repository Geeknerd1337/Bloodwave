#include "WaveManager.h"
#include "../ObjectManager.h"
#include "../Objects/Enemy.h"
#include "../Objects/MiniBoss.h"
void WaveManager::Initialize() {
	m_tTimeSinceLastWave.SetTimeSince(0.0f);
	
}


void WaveManager::Simulate() {
	
	//Start the wave if it hasn't been started yet
	if (m_tTimeSinceLastWave.GetTimeSince() > m_fTimeBetweenWaves) {
		if (!m_bWaveStarted) {
			StartWave();
			m_bWaveStarted = true;
		}

		
	}


	//Continually reset wave timer
	if (!m_bWaveStarted) {
		printf("%f Seconds Until Wave\n", m_fTimeBetweenWaves - m_tTimeSinceLastWave.GetTimeSince());
	}


	if (m_bWaveStarted) {
		//printf("%d Enemies Remain\n", EnemyCount());
		if (EnemyCount() <= 0) {
			EndWave();
		}
	}
}

void WaveManager::EndWave() {
	m_bWaveStarted = false;
	m_tTimeSinceLastWave.SetTimeSince(0.0f);
	m_iEnemiesPerWave += 5;
	//printf("wave Ended\n");
}

void WaveManager::StartWave() {
	//printf("Wave Start\n");
	
	//if current wave counter != 4, spawn enemies normally
	if (m_iCurrentWave != 4) {
		//Spawn enemies
		for (int i = 0; i < m_iEnemiesPerWave; i++) {
			Vector2 pos;
			int edge = rand() % 4;

			//I'm using magic numbers here because I want this in the demo tonight
			//Josh Wilson
			switch (edge) {
			case 0:
				pos = Vector2(2100, rand() % 2048);
				break;
			case 1:
				pos = Vector2(-100, rand() % 2048);
				break;
			case 2:
				pos = Vector2(rand() % 2048, -100);
				break;
			case 3:
				pos = Vector2(rand() % 2048, 2100);
				break;
			}

			m_pObjectManager->create(eSprite::Enemy_Idle, pos);
		}
	}
	
	//if the current wave counter == 4 (i.e. it's wave 5 by the time simulate calls this),  spawn mini boss
	if (m_iCurrentWave == 4) {
		SpawnMiniBoss();
	}
	
	m_iCurrentWave++;
}

int WaveManager::EnemyCount(){
int count = 0;
//Iterate over m_stdObjectList on the object manager and increment count if the object is an enemy
for (auto it = m_pObjectManager->m_stdObjectList.begin(); it != m_pObjectManager->m_stdObjectList.end(); it++) {
	if (dynamic_cast<CEnemy*>(*it) != nullptr) {
		count++;
	}
}
return count;
}

void WaveManager::SpawnMiniBoss() {
	for (int i = 0; i < 1; i++) {
		m_pObjectManager->create(eSprite::Mini_Boss_Idle, Vector2(1024.0f, 1024.0f));
	}
}