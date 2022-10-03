/// \file Game.h
/// \brief Interface for the game class CGame.

#ifndef __L4RC_GAME_GAME_H__
#define __L4RC_GAME_GAME_H__

#include "Component.h"
#include "Common.h"
#include "ObjectManager.h"
#include "Settings.h"
#include "Player.h"
#include "Utility/GameCamera.h"

/// \brief The game class.
///
/// The game class is the object-oriented implementation of the game. This class
/// must contain the following public member functions. `Initialize()` does
/// initialization and will be run exactly once at the start of the game.
/// `ProcessFrame()` will be called once per frame to create and render the
/// next animation frame. `Release()` will be called at game exit but before
/// any destructors are run.

class CGame :
	public LComponent,
	public LSettings,
	public CCommon {
	friend class GameCamera;
private:
	bool m_bDrawFrameRate = false; ///< Draw the frame rate.
	std::string m_sConsoleOutput = "";

	void LoadImages(); ///< Load images.
	void LoadSounds(); ///< Load sounds.
	void BeginGame(); ///< Begin playing the game.
	void KeyboardHandler(); ///< The keyboard handler.
	void ControllerHandler(); ///< The controller handler.
	void RenderFrame(); ///< Render an animation frame.
	void DrawFrameRateText(); ///< Draw frame rate text to screen.
	void CreateObjects(); ///< Create game objects.
	void FollowCamera(); ///< Make camera follow player character.

	static CGame* instance; // use nullptr since C++11


public:
	~CGame(); ///< Destructor.

	void Initialize(); ///< Initialize the game.
	void ProcessFrame(); ///< Process an animation frame.
	void Release(); ///< Release the renderer.

	void AddConsoleOutput(std::string s);

	void DrawConsoleText();

	static CGame* Instance(); ///< Return the instance of the game.
	//Static Game Camera
	static GameCamera* camera;


}; //CGame

#endif //__L4RC_GAME_GAME_H__
