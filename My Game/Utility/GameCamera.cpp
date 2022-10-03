#include "GameCamera.h"
#include "../Game.h"
#include "SimpleMath.h"


void GameCamera::HandleCamera() {
	if (m_pPlayer == nullptr)return; //safety
	//Get the game instance
	CGame* pGame = CGame::Instance();
	const float deltaTime = m_pTimer->GetFrameTime();

	Vector3 vCameraPos(m_pPlayer->GetPos()); //player position

	if (m_vWorldSize.x > pGame->m_nWinWidth) { //world wider than screen
		vCameraPos.x = std::max(vCameraPos.x, pGame->m_nWinWidth / 2.0f); //stay away from the left edge
		vCameraPos.x = std::min(vCameraPos.x, m_vWorldSize.x - pGame->m_nWinWidth / 2.0f);  //stay away from the right edge
	} //if
	else vCameraPos.x = m_vWorldSize.x / 2.0f; //center horizontally.

	if (m_vWorldSize.y > pGame->m_nWinHeight) { //world higher than screen
		vCameraPos.y = std::max(vCameraPos.y, pGame->m_nWinHeight / 2.0f);  //stay away from the bottom edge
		vCameraPos.y = std::min(vCameraPos.y, m_vWorldSize.y - pGame->m_nWinHeight / 2.0f); //stay away from the top edge
	} //if
	else vCameraPos.y = m_vWorldSize.y / 2.0f; //center vertically

	m_cameraPos = Vector3::Lerp(m_cameraPos, vCameraPos, deltaTime);

	m_pRenderer->SetCameraPos(m_cameraPos); //camera to player
} //FollowCamera