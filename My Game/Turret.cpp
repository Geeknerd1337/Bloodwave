/// \file Turret.cpp
/// \brief Code for the turret object class CTurret.

#include "Turret.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Helpers.h"

/// Create and initialize a turret object given its position.
/// \param p Position of turret.

CTurret::CTurret(const Vector2& p): CObject(eSprite::Turret, p){
  m_bStatic = true; //turrets are static
} //constructor

/// Rotate the turret and fire the gun at at the closest available target if
/// there is one, and rotate the turret at a constant speed otherwise.

void CTurret::move(){
  const float dMin = 256.0f; //minimum distance at which target is invisible
  const float dMinSq = dMin*dMin; //that squared

  CObject* pTarget = nullptr; //pointer to closest target
  float dsq = FLT_MAX; //distance squared to closest target

  m_pObjectManager->FindClosest(m_vPos, pTarget, dsq); //find closest target

  if(pTarget && dsq < dMinSq) //if in range
    RotateTowards(pTarget->m_vPos); //rotate towards target
  else m_fRotSpeed = 0.4f; //no target in range, so scan

  m_fRoll += 0.2f*m_fRotSpeed*XM_2PI*m_pTimer->GetFrameTime(); //rotate
  NormalizeAngle(m_fRoll); //normalize to [-pi, pi] for accuracy
} //move

/// Rotate the turrent towards a point and file the gun if it is facing
/// sufficiently close to it.
/// \param pos Target point.

void CTurret::RotateTowards(const Vector2& pos){
  const Vector2 v = pos - m_vPos; //vector from target to turret
  const float theta = atan2f(v.y, v.x); //orientation of that vector
  float diff = m_fRoll - theta; //difference with turret orientation
  NormalizeAngle(diff); //normalize to [-pi, pi]

  //set rotation speed from diff

  const float fAngleDelta = 0.05f; //allowable angle discrepancy
  const float fTrackingSpeed = 2.0f; //rotation speed when tracking

  if(diff > fAngleDelta)m_fRotSpeed = -fTrackingSpeed; //clockwise
  else if(diff < -fAngleDelta)m_fRotSpeed = fTrackingSpeed; //counterclockwise
  else m_fRotSpeed = 0; //stop rotating

  //fire gun if pointing approximately towards target

  if(fabsf(diff) < fAngleDelta && m_pGunFireEvent->Triggered())
    m_pObjectManager->FireGun(this, eSprite::Bullet2);
} //RotateTowards

/// Response to collision. If colliding with an object, play a sound.
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

void CTurret::CollisionResponse(const Vector2& norm, float d, CObject* pObj){
  if(pObj && pObj->isBullet())
    m_pAudio->play(eSound::Clang);
} //CollisionResponse