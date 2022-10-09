#pragma once
#include "../Player.h"
#include "../Common.h"
#include "ComponentIncludes.h"

class CGame;

class GameCamera : public CCommon, public LComponent {
public:
	void HandleCamera();
	
private:
	Vector3 m_cameraPos;

};