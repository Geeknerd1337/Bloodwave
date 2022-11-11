/// \file Object.cpp
/// \brief Code for the game object class CObject.

#include "Object.h"
#include "ComponentIncludes.h"
#include "GameDefines.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Helpers.h"

/// Create and initialize an object given its sprite type and initial position.
/// \param t Type of sprite.
/// \param p Initial position of object.

CObject::CObject(eSprite t, const Vector2& p) :
	LBaseObject(t, p)
{
	m_fRoll = XM_PIDIV2; //facing upwards
	m_bIsTarget = false; //not a target

	const float w = m_pRenderer->GetWidth(t); //sprite width
	const float h = m_pRenderer->GetHeight(t); //sprite height

	if (m_vBounds == Vector3::Zero) {
		m_vBounds = Vector3(w, h, 0.0f); //bounding box
	}
	
	m_fRadius = std::max(w, h) / 2; //bounding circle radius

	// Set the initial frame timer for the object.
	m_pFrameEvent = new LEventTimer((1.0/60.0) * m_fImageSpeed); 
} 

/// Destructor.

CObject::~CObject() {

} //destructor

/// <summary>
/// Sets the current sprite index to a given value.
/// </summary>
/// <param name="newSprite"></param>
void CObject::SetSprite(eSprite newSprite) {
	//If the current sprite and the new sprite match, return
	if (m_nSpriteIndex  == (UINT) newSprite) {
		return;
	}
	

	m_nCurrentFrame = 0;
	m_nSpriteIndex = (UINT)newSprite;
}

const Vector2& CObject::GetPos() const {
	return m_vPos;
} //GetPos



//BuildInput
void CObject::buildInput()
{
	//Build the input for the object
}

void CObject::simulate() {
	m_iDepth = (int)m_vPos.y;
	UpdateFramenumber();
}

/// Move object an amount that depends on its velocity and the frame time.
void CObject::move() {
	if (!m_bDead && !m_bStatic)
		m_vPos += m_vVelocity * m_pTimer->GetFrameTime();
} //move

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `CObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `CObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void CObject::draw() {
	m_pRenderer->Draw(this);
	BoundingBox b;
	b.Center = Vector3(m_vPos.x, m_vPos.y, 0);
	b.Extents = m_vBounds * 0.5f;
	//m_pRenderer->DrawBoundingBox(eSprite::Small_Square,b);
} //draw

/// Response to collision. Move back the overlap distance along the collision
/// normal. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

void CObject::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {
	if (m_bDead)return; //dead, bail out

	const Vector2 vOverlap = d * norm; //overlap in direction of this
	const bool bStatic = !pObj || pObj->m_bStatic; //whether other object is static

	if (!m_bStatic && !bStatic) //both objects are dynamic
		m_vPos += vOverlap / 2; //back off this object by half

	else if (!m_bStatic && bStatic) //only this object is dynamic
		m_vPos += vOverlap; //back off this object
} //CollisionResponse

/// Create a particle effect to mark the death of the object.
/// This function is a stub intended to be overridden by various object classes
/// derived from this class.

void CObject::DeathFX() {
	//stub
} //DeathFX

/// Compute the view vector from the object orientation.
/// \return The view vector.

const Vector2 CObject::GetViewVector() const {
	return AngleToVector(m_fRoll);
} //ViewVector

/// Reader function for bullet flag.
/// \return true if a bullet.

const bool CObject::isBullet() const {
	return m_bIsBullet;
} 


void CObject::ImageLooped(eSprite sprite) {
	//Check here
}

//Updating the frame number to be incremented every time the frame event runs
void CObject::UpdateFramenumber() {
	//This gets the number of frames in the current sprite sheet
	const size_t n = m_pRenderer->GetNumFrames(m_nSpriteIndex); 

	if (m_fImageSpeed <= 0.0f) {
		return;
	}
	
	//If there's more than one frame, and the event has been triggered
	if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered()) {
		//Trigger the frame event again at a given delay
		m_pFrameEvent->SetDelay((1.0 / 60.0) * m_fImageSpeed);

		//Check the next frame
		int nextFrame = (m_nCurrentFrame + 1 & n);
		//If the next frame is zero, then we've reached the end of the animation, do the image call back
		if (m_nCurrentFrame == 0) {
			ImageLooped((eSprite)m_nSpriteIndex);
		}

		//Incrementing the current frame up by one. 
		m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
	} 
}