#pragma once
#include "../Player.h"
#include "../Common.h"
#include "ComponentIncludes.h"
#include "TimeSince.h"
#include <vector>

class CGame;

/// <summary>
/// Defining this class in it's entirety here because it is purely informational
/// This is essentially how we handle multiple 
/// TODO: Upgrade this a bit so that we can have smoothing on the shake
/// </summary>
class ShakeInstance : public CCommon {
public:
	TimeSince m_tTimeSinceStarted;
	float m_duration;
	float m_xMagnitude;
	float m_yMagnitude;

	ShakeInstance(float duration, float xMagnitude, float yMagnitude) {
		m_duration = duration;
		m_xMagnitude = xMagnitude;
		m_yMagnitude = yMagnitude;
		m_tTimeSinceStarted.SetTimeSince(0.0f);
	}
};

class GameCamera : public CCommon, public LComponent {
public:
	void HandleCamera();
	Vector3 m_cameraPos;
	std::vector<ShakeInstance> m_vShakeInstances;

	void Shake(float duration, Vector2 magnitude);
	
	~GameCamera();
	
private:
	

};

