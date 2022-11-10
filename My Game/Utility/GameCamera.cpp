#include "GameCamera.h"
#include "../Game.h"
#include "SimpleMath.h"
#include <random>

void GameCamera::HandleCamera() {
	//Ensure the player exists
	if (m_pPlayer == nullptr)return; 
	//Get the game instance
	CGame* pGame = CGame::Instance();

	//Get the delta time
	const float deltaTime = m_pTimer->GetFrameTime();

	//Get the player position in the world
	Vector3 vCameraPos(m_pPlayer->GetPos());

	if (m_vWorldSize.x > pGame->m_nWinWidth) { //world wider than screen
		vCameraPos.x = std::max(vCameraPos.x, pGame->m_nWinWidth / 2.0f); //stay away from the left edge
		vCameraPos.x = std::min(vCameraPos.x, m_vWorldSize.x - pGame->m_nWinWidth / 2.0f);  //stay away from the right edge
	} //if
	else vCameraPos.x = m_vWorldSize.x / 2.0f; //center horizontally.

	if (m_vWorldSize.y > pGame->m_nWinHeight) { //world higher than screen
		vCameraPos.y = std::max(vCameraPos.y, pGame->m_nWinHeight / 2.0f);  //stay away from the bottom edge
		vCameraPos.y = std::min(vCameraPos.y, m_vWorldSize.y - pGame->m_nWinHeight / 2.0f); //stay away from the top edge
	} //if
	else vCameraPos.y = m_vWorldSize.y / 2.0f;

	Vector2 shakeOffset;
	
	//Iterate through all the shake instances adding a random value between the magnitude and the negative magnitude of the shake instance
	for (int i = 0; i < m_vShakeInstances.size(); i++) {
		ShakeInstance instance = m_vShakeInstances[i];
		//If the shake instance has expired, remove it
		if (instance.m_tTimeSinceStarted.GetTimeSince() > instance.m_duration) {
			m_vShakeInstances.erase(m_vShakeInstances.begin() + i);
			continue;
		}
		
		//Supposedly a much more accurate and more performant method of doing random numbers
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-1, 1);
		shakeOffset.x += dis(gen) * instance.m_xMagnitude;
		shakeOffset.y += dis(gen) * instance.m_yMagnitude;
	}
	
	//Smoothly go to the new camera position with the shake offset added
	m_cameraPos = Vector3::SmoothStep(m_cameraPos, vCameraPos, deltaTime * 10.0) + shakeOffset;

	m_pRenderer->SetCameraPos(m_cameraPos); //camera to player
} //FollowCamera

//Add a new instance of shake to the vector
void GameCamera::Shake(float duration, Vector2 magnitude) {
	m_vShakeInstances.push_back(ShakeInstance(duration, magnitude.x, magnitude.y));
}

//Delete all the shake instances from the vector in the destructor, making sure to free them up from memory
GameCamera::~GameCamera() {
	for (int i = 0; i < m_vShakeInstances.size(); i++) {
		delete& m_vShakeInstances[i];
	}
	m_vShakeInstances.clear();
}