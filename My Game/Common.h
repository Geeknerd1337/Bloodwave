/// \file Common.h
/// \brief Interface for the class CCommon.

#ifndef __L4RC_GAME_COMMON_H__
#define __L4RC_GAME_COMMON_H__

#include "Defines.h"
#include "Utility/Rendering/BloodWaveRenderer.h"


//forward declarations to make the compiler less stroppy
//comment for github

class CObjectManager; 
class LSpriteRenderer;
class LParticleEngine2D;
class CPlayer;
class CEnemy;
class GameCamera;
class CMouse;
class Canvas;
class BloodWaveRenderer;
class WaveManager;
class CMiniBoss;

/// \brief The common variables class.
///
/// CCommon is a singleton class that encapsulates things that are common to
/// different game components, including game state variables. Making it a
/// singleton class means that we can avoid passing its member variables
/// around as parameters, which makes the code minisculely faster, and more
/// importantly, makes the code more readable by reducing function clutter.

class CCommon{
  protected:  
    static BloodWaveRenderer* m_pRenderer; ///< Pointer to renderer.
    static CObjectManager* m_pObjectManager; ///< Pointer to object manager.
    static LParticleEngine2D* m_pParticleEngine; ///< Pointer to particle engine.    
    static CMouse* m_pMouse; ///< The mouse.
    static Vector2 m_vWorldSize; ///< World height and width.
    static CPlayer* m_pPlayer; ///< Pointer to player character.
    static GameCamera* m_pCamera;
	static Canvas* m_pCanvas;
    static WaveManager* m_pWaveManager;
    static CMiniBoss* m_pMiniBoss;
}; //CCommon

#endif //__L4RC_GAME_COMMON_H__