/// \file Ant.cpp
/// \brief Code for the ant object class CAnt.

#include "Ant.h"
#include "ComponentIncludes.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Helpers.h"

/// Create and initialize an ant object given its initial position.
/// \param pos Initial position of ant.

CAnt::CAnt(const Vector2& pos):
  CObject(eSprite::Ant, pos), 
  m_bPreferPosRot(m_pRandom->randf() < 0.5f)
{
  m_fRoll = -XM_PIDIV2; //facing up
  m_vVelocity = Vector2(0.0f, 64.0f); //going up
  m_fXScale = m_fYScale = 0.5f; //scale
  m_fRadius *= m_fXScale; //scale the bounding circle radius

  m_pFrameEvent = new LEventTimer(0.1f);
  m_pStrayEvent = new LEventTimer(5.0f, 2.0f);

  m_bIsTarget = true;
  m_bStatic = false;
} //constructor

/// Destructor.

CAnt::~CAnt(){
  delete m_pFrameEvent;
  delete m_pStrayEvent;
} //destructor

/// Move and advance current frame number. Also stray randomly from current path.

void CAnt::move(){ 
  CObject::move(); //move like a default object
  StrayFromPath(); //stray randomly left or right
  UpdateFramenumber(); //choose current frame
} //move

/// Adjust direction randomly at random intervals.

void CAnt::StrayFromPath(){  
  const float t = m_pTimer->GetTime(); //current time
  
  if(m_pStrayEvent && m_pStrayEvent->Triggered()){ //enough time has passed
    const float delta = (m_bStrayParity? -1.0f: 1.0f)*0.1f; //angle delta

    m_vVelocity = RotateVector(m_vVelocity, delta); //change direction by delta
    m_fRoll += delta; //rotate to face that direction

    m_bStrayParity = m_pRandom->randf() < 0.5f; //next stray is randomly left or right 
  } //if
} //StrayFromPath

/// Update the frame number in the animation sequence.

void CAnt::UpdateFramenumber(){
  const size_t n = m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of frames

  if(n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered()){
    m_pFrameEvent->SetDelay(100.0f/(1500.0f + fabsf(m_fSpeed)));
    m_nCurrentFrame = (m_nCurrentFrame + 1)%n; 
  } //if
} //UpdateFramenumber

/// Response to collision. If the ant is facing the object that is colliding
/// with, then it rotates in its preferred direction and then calls 
/// CObject::CollisionResponse. Note that the only reason that colliding
/// ants won't be facing each other is in the case of multiple ants colliding
/// and pushing one of them in some direction other than the one in which
/// it is facing. Howerver, faster objects such as the player objact can
/// collide from behind.
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to nullptr,
/// which means collision with a wall).

void CAnt::CollisionResponse(const Vector2& norm, float d, CObject* pObj){
  const float t = m_pTimer->GetFrameTime(); //frame time

  //start rotating if hit from behind

  if( m_vVelocity.Dot(norm) < 0 && this > pObj){ 
    const float delta = 4.0f*(m_bPreferPosRot? 1: -1)*t; //rotation delta
    m_vVelocity = RotateVector(m_vVelocity, delta); //rotate velocity
    m_fRoll += delta; //face the correct direction
  } //else

  //jump if hit by a bullet

  if(pObj && pObj->isBullet()){
    m_pAudio->play(eSound::Ow);
    m_vVelocity = m_vVelocity.Length()*norm;
    m_fRoll = XM_PI + atan2f(m_vVelocity.y, m_vVelocity.x);
  } //if

  CObject::CollisionResponse(norm, d, pObj); //default collision response
} //CollisionResponse
