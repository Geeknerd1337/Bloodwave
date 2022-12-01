/// \file Common.cpp
/// \brief Code for the class CCommon.
///
/// This file contains declarations and initial values
/// for CCommon's static member variables.

#include "Common.h"


BloodWaveRenderer* CCommon::m_pRenderer = nullptr;
CObjectManager* CCommon::m_pObjectManager = nullptr;
LParticleEngine2D* CCommon::m_pParticleEngine = nullptr;
CMouse* CCommon::m_pMouse = nullptr;

Vector2 CCommon::m_vWorldSize = Vector2::Zero;
CPlayer* CCommon::m_pPlayer = nullptr;
GameCamera* CCommon::m_pCamera = nullptr;
Canvas* CCommon::m_pCanvas = nullptr;
WaveManager* CCommon::m_pWaveManager = nullptr;

CMiniBoss* CCommon::m_pMiniBoss = nullptr;