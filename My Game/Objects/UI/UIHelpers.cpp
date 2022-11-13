#include "UIHelpers.h"
#include "../../Utility/GameCamera.h"

Vector2 UIHelpers::GetScreenPos()
{
	Vector2 windowOffset = Vector2(m_pCanvas->m_nWidth / 2.0, m_pCanvas->m_nHeight / 2.0);
	Vector2 screenPos = m_pCamera->m_cameraPos - windowOffset;
	return screenPos;
}