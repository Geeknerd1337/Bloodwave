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
  friend class CObjectManager; ///< Object manager needs access so it can manage.

  protected:
    float m_fRadius = 0; ///< Bounding circle radius.

    float m_fSpeed = 0; ///< Speed.
    float m_fRotSpeed = 0; ///< Rotational speed.
    Vector2 m_vVelocity; ///< Velocity.
    bool m_bStatic = true; ///< Is static (does not move).
    bool m_bIsTarget = true; ///< Is a target.
    bool m_bIsBullet = false; ///< Is a bullet.

    LEventTimer* m_pGunFireEvent = nullptr; ///< Gun fire event.
    
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
    void simulate();

    /// <summary>
    /// A method responsible for moving the object in the world. This is called after simulate.
    /// </summary>
    void move();

    /// <summary>
    /// A method which is responsible for actually drawing the object, called last
    /// </summary>
    void draw();

    void SetSprite(eSprite);


    const bool isBullet() const; ///< Is a bullet.
}; //CObject

#endif //__L4RC_GAME_OBJECT_H__