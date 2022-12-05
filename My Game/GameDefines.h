/// \file GameDefines.h
/// \brief Game specific defines.

#ifndef __L4RC_GAME_GAMEDEFINES_H__
#define __L4RC_GAME_GAMEDEFINES_H__

#include "Defines.h"

/// \brief Sprite enumerated type.
///
/// An enumerated type for the sprites, which will be cast to an unsigned
/// integer and used for the index of the corresponding texture in graphics
/// memory. `Size` must be last.

enum class eSprite : UINT {
	Background, Bullet, Bullet2, Player, Turret, Smoke, Spark, Ant,
	Player_Idle, Player_Idle_Left, Player_Idle_Right, Player_Walk_Left, Player_Walk_Right, 
	Player_Attack_Left, Player_Attack_Right,
	Enemy_Idle, Enemy_Idle_Left, Enemy_Idle_Right, Enemy_Walk_Left, Enemy_Walk_Right, Enemy_Dead,
	Mini_Boss_Idle,
	Small_Square, Health_Pip, Fade_Object, Single_Pixel, Small_Circle,
	Blood_Particle, Blood_Pool,Monster_Gib,
	SpriteSheet, AntSpriteSheet, PlayerWalkSpriteSheetLeft, PlayerWalkSpriteSheetRight,
	PlayerAttackSpriteSheetLeft, PlayerAttackSpriteSheetRight,
	EnemyWalkSpriteSheetLeft, EnemyWalkSpriteSheetRight, Tile, TileSheet,
	SpitterEnemyWalkSpriteSheetLeft, SpitterEnemyWalkSpriteSheetRight,
	Melee_Swipe_Sheet, Melee_Swipe, Diamond,
	Ability_Health, 
	SpitterEnemy_Idle, SpitterEnemy_Idle_Right, SpitterEnemy_Walk_Left, SpitterEnemy_Walk_Right, SpitterEnemy_Dead,
	SpitterMonster_Gib, Acid, Win, Loose, Shield, IconDrop, 
	Size  //MUST BE LAST
}; //eSprite

/// \brief Sound enumerated type.
///
/// An enumerated type for the sounds, which will be cast to an unsigned
/// integer and used for the index of the corresponding sample. `Size` must 
/// be last.

enum class eSound : UINT {
	Clang, Grunt, Gun, Ricochet, Ow,Synth, Hit, Whoosh, PowerUp, GameOver, Sword, eHit,
	Size  //MUST BE LAST
}; //eSound

/// <summary>
/// The player state is an enumeration representing the current state of the player. This is used with a FSM
/// to control the player logic in the CPlayer class.
/// </summary>
enum class ePlayerState : UINT {
	Idle, Attack, Stun, Dead, Dash
};

/// <summary>
/// This represents the current state of the enemy. This is used with an FSM in the CEnemy class to
/// effectively manage the AI of our enemy class.
/// </summary>
enum class eEnemyState {
	Idle, Chase, Attack, Stun, Dead
};


/// <summary>
/// Adding this for centering text horizontally
/// </summary>
enum class HorizontalAlignment{
	Left, Center, Right
};

/// <summary>
/// Adding this for centering text vertically
/// </summary>
enum class VerticalAlignment {
	Top, Center, Bottom
};

#endif //__L4RC_GAME_GAMEDEFINES_H__