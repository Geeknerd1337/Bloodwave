/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"

#include "shellapi.h"
#include <iostream>

//Singleton
CGame* CGame::instance = nullptr;
GameCamera* CGame::camera = nullptr;

//This is a singleton instance which can be accessed via any class that includes
//game.h. This is so we can access any global functions if needed.
CGame* CGame::Instance() {
	return instance;
} //Instance


/// Delete the particle engine and the object manager. The renderer needs to
/// be deleted before this destructor runs so it will be done elsewhere.

CGame::~CGame() {
	delete m_pParticleEngine;
	delete m_pObjectManager;
	delete camera;
} //destructor

/// Create the renderer, the object manager, and the particle engine, load
/// images and sounds, and begin the game.
/// 
void CGame::Initialize() {

	m_pRenderer = new LSpriteRenderer(eSpriteMode::Batched2D);
	m_pRenderer->Initialize(eSprite::Size);
	LoadImages(); //load images from xml file list

	m_pObjectManager = new CObjectManager; //set up the object manager 
	LoadSounds(); //load the sounds for this game

	m_pParticleEngine = new LParticleEngine2D(m_pRenderer);

	//Set the instance
	instance = this;

	//Set the camera
	camera = new GameCamera();

	BeginGame();

} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages() {
	m_pRenderer->BeginResourceUpload();

	m_pRenderer->Load(eSprite::Background, "floor");

	m_pRenderer->Load(eSprite::SpriteSheet, "spritesheet"); //must be loaded before its sprites

	m_pRenderer->Load(eSprite::Player, "player");
	m_pRenderer->Load(eSprite::Bullet, "bullet");
	m_pRenderer->Load(eSprite::Bullet2, "bullet2");
	m_pRenderer->Load(eSprite::Smoke, "smoke");
	m_pRenderer->Load(eSprite::Spark, "spark");
	m_pRenderer->Load(eSprite::Turret, "turret");

	//Player
	m_pRenderer->Load(eSprite::Player_Idle, "player_idle");
	m_pRenderer->Load(eSprite::Player_Idle_Left, "player_idle_left");
	m_pRenderer->Load(eSprite::Player_Idle_Right, "player_idle_right");

	//Enemy
	m_pRenderer->Load(eSprite::Enemy_Idle, "enemy_idle");
	m_pRenderer->Load(eSprite::Enemy_Idle_Left, "enemy_idle_left");
	m_pRenderer->Load(eSprite::Enemy_Idle_Right, "enemy_idle_right");

	m_pRenderer->Load(eSprite::AntSpriteSheet, "antwalk"); //must be loaded before its sprites
	m_pRenderer->Load(eSprite::Ant, "ant");

	m_pRenderer->EndResourceUpload();
} //LoadImages

/// Initialize the audio player and load game sounds.

void CGame::LoadSounds() {
	m_pAudio->Initialize(eSound::Size);

	m_pAudio->Load(eSound::Ow, "ow");
	m_pAudio->Load(eSound::Grunt, "grunt");
	m_pAudio->Load(eSound::Clang, "clang");
	m_pAudio->Load(eSound::Gun, "gun");
	m_pAudio->Load(eSound::Ricochet, "ricochet");
} //LoadSounds

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release() {
	delete m_pRenderer;
	m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create a player object, some ants, and a turret.

void CGame::CreateObjects() {
	//m_pRenderer->GetSize(eSprite::Background, m_vWorldSize.x, m_vWorldSize.y); //init m_vWorldSize
	m_vWorldSize.x = 4096;
	m_vWorldSize.y = 4096;

	m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::Player_Idle, Vector2(64.0f, 64.0f));
	(CEnemy*)m_pObjectManager->create(eSprite::Enemy_Idle, Vector2(64.0f, 64.0f));
	
	m_pObjectManager->create(eSprite::Turret, Vector2(430.0f, 430.0f));

	Vector2 v(128.0f, 64.0f); //initial ant position

	for (int i = 0; i < 12; i++) {
		m_pObjectManager->create(eSprite::Ant, v);
		v.x += 64.0f;
	} //for
} //CreateObjects

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program. Clear the particle engine to get rid of any existing particles,
/// delete any old objects out of the object manager and create some new ones.

void CGame::BeginGame() {
	m_pParticleEngine->clear(); //clear old particles
	m_pObjectManager->clear(); //clear old objects
	CreateObjects(); //create new objects 
} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler() {
	m_pKeyboard->GetState(); //get current keyboard state 

	if (m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
		m_bDrawFrameRate = !m_bDrawFrameRate;

	if (m_pKeyboard->TriggerDown(VK_BACK)) //start game
		BeginGame(); 
}

/// Poll the XBox controller state and respond to the controls there.

void CGame::ControllerHandler() {
	if (!m_pController->IsConnected())return;

	m_pController->GetState(); //get state of controller's controls 

} //ControllerHandler

/// Draw the current frame rate to a hard-coded position in the window.
/// The frame rate will be drawn in a hard-coded position using the font
/// specified in `gamesettings.xml`.

void CGame::DrawFrameRateText() {
	const std::string s = std::to_string(m_pTimer->GetFPS()) + " fps"; //frame rate
	const Vector2 pos(m_nWinWidth - 128.0f, 30.0f); //hard-coded position
	m_pRenderer->DrawScreenText(s.c_str(), pos); //draw to screen
} //DrawFrameRateText

//Draw the current console output
void CGame::DrawConsoleText() {
	const Vector2 pos(0.0f, 0.0f); //hard-coded position
	m_pRenderer->DrawScreenText(m_sConsoleOutput.c_str(), pos); //draw to screen
} //DrawConsoleText

/// Ask the object manager to draw the game objects. The renderer is notified of
/// the start and end of the frame so that it can let Direct3D do its
/// pipelining jiggery-pokery.

void CGame::RenderFrame() {
	m_pRenderer->BeginFrame(); //required before rendering

	m_pRenderer->Draw(eSprite::Background, m_vWorldSize / 2.0f); //draw background
	m_pObjectManager->draw(); //draw objects 
	m_pParticleEngine->Draw(); //draw particles
	//Useful method for drawing frame text
	if (m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
	DrawConsoleText(); //draw console output

	m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// Make the camera follow the player, but don't let it get too close to the
/// edge unless the world is smaller than the window, in which case we just
/// center everything.

void CGame::FollowCamera() {
	if (m_pPlayer == nullptr)return; //safety
	Vector3 vCameraPos(m_pPlayer->GetPos()); //player position

	if (m_vWorldSize.x > m_nWinWidth) { //world wider than screen
		vCameraPos.x = std::max(vCameraPos.x, m_nWinWidth / 2.0f); //stay away from the left edge
		vCameraPos.x = std::min(vCameraPos.x, m_vWorldSize.x - m_nWinWidth / 2.0f);  //stay away from the right edge
	} //if
	else vCameraPos.x = m_vWorldSize.x / 2.0f; //center horizontally.

	if (m_vWorldSize.y > m_nWinHeight) { //world higher than screen
		vCameraPos.y = std::max(vCameraPos.y, m_nWinHeight / 2.0f);  //stay away from the bottom edge
		vCameraPos.y = std::min(vCameraPos.y, m_vWorldSize.y - m_nWinHeight / 2.0f); //stay away from the top edge
	} //if
	else vCameraPos.y = m_vWorldSize.y / 2.0f; //center vertically

	m_pRenderer->SetCameraPos(vCameraPos); //camera to player
} //FollowCamera

/// This function will be called regularly to process and render a frame
/// of animation, which involves the following. Handle keyboard input.
/// Notify the  audio player at the start of each frame so that it can prevent
/// multiple copies of a sound from starting on the same frame.  
/// Move the game objects. Render a frame of animation. 

void CGame::ProcessFrame() {
	ControllerHandler(); //handle controller input
	KeyboardHandler(); //handle keyboard input;
	
	m_pObjectManager->BuildInput();
	
	m_pAudio->BeginFrame(); //notify audio player that frame has begun

	m_pTimer->Tick([&]() { //all time-dependent function calls should go here
		m_pObjectManager->move(); //move all objects
		//FollowCamera(); //make camera follow player
		camera->HandleCamera();
		m_pParticleEngine->step(); //advance particle animation
		});

	RenderFrame(); //render a frame of animation
} //ProcessFrame


void CGame::AddConsoleOutput(const std::string s) {
	m_sConsoleOutput += s + "\n";
}

