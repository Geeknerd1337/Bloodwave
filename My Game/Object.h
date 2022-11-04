/// \file Object.h
/// \brief Interface for the game object class CObject.

#ifndef __L4RC_GAME_OBJECT_H__
#define __L4RC_GAME_OBJECT_H__

#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "BaseObject.h"
#include "EventTimer.h"

/// \brief The game object. 
///
/// The abstract representation of an object. `CObjectManager` is a friend of
/// this class so that it can access any private members as needed to manage
/// the objects without the need for reader and set functions for each private
/// or protected member variable. This class must contain public member
/// functions `move()` and `draw()` to move and draw the object, respectively.

class CObject:
  public CCommon,
  public LBaseObject
{
  friend class CObjectManager;

  protected:
    float m_fRadius = 0; ///< Bounding circle radius.
    Vector3 m_vBounds = Vector3(0.0f, 0.0f, 0.0f);
    float m_fRotSpeed = 0; ///< Rotational speed.
    
    /// <summary>
	/// Represents the velocity of the object where the x and y components make up the horizontal and vertical components of the velocity, respectively.
    /// </summary>
    Vector2 m_vVelocity;
	
	
    //TODO: Remove these
    bool m_bStatic = true; ///< Is static (does not move).
    bool m_bIsTarget = true; ///< Is a target.
    bool m_bIsBullet = false; ///< Is a bullet.

    /// <summary>
    /// Scalar float representing how fast our image goes relative to 60 frames a second
    /// </summary>
    float m_fImageSpeed = 1;
	
    /// <summary>
    /// An event for updating our frame number
    /// </summary>
    LEventTimer* m_pFrameEvent = nullptr;

    /// <summary>
    /// Updates the frame, called from simulate method.
    /// </summary>
    void UpdateFramenumber();
    
    virtual void CollisionResponse(const Vector2&, float,
      CObject* = nullptr); ///< Collision response.
    virtual void DeathFX(); ///< Death special effects.

    const Vector2 GetViewVector() const; ///< Compute view vector.

  public:
    CObject(eSprite, const Vector2&); ///< Constructor.
    virtual ~CObject(); ///< Destructor.
	
    /// <summary>
	/// Build Input is called every frame and is responsible for handling input on a per object basis. This is called before simulate.
    /// </summary>
    virtual void buildInput();

    /// <summary>
    /// This method handles the simulation of all objects. It is where we will put game logic for each individual object
	/// and gets called after buildInput() and before draw()
    /// </summary>
    virtual void simulate();

    /// <summary>
    /// A method responsible for moving the object in the world. This is called after simulate.
    /// </summary>
    void move();

    /// <summary>
    /// A method which is responsible for actually drawing the object, called last
    /// </summary>
    void draw();

    void SetSprite(eSprite);

    const Vector2& GetPos() const; ///< Get position.


    const bool isBullet() const; ///< Is a bullet.
}; //CObject

#endif //__L4RC_GAME_OBJECT_H__