/// \file ObjectManager.h
/// \brief Interface for the object manager CObjectManager.

#ifndef __L4RC_GAME_OBJECTMANAGER_H__
#define __L4RC_GAME_OBJECTMANAGER_H__

#include "BaseObjectManager.h"
#include "Object.h"
#include "Common.h"
#include <vector>
#include <string>

/// <summary>
/// A collection of all the game objects in the game
/// </summary>
class CObjectManager :
	public LBaseObjectManager<CObject>,
	public CCommon
{
private:
	void BroadPhase(); ///< Broad phase collision detection and response.
	void NarrowPhase(CObject*, CObject*); ///< Narrow phase collision detection and response.
	bool AtWorldEdge(CObject*, Vector2&, float&) const; ///< Test whether at the edge of the world.

public:
	CObject* create(eSprite, const Vector2&); ///< Create new object.
	CObject* createDirect(CObject* obj);


	/// <summary>
	/// TODO: Remove this function, there's no reason this should be in the object manager
	/// </summary>
	void FireGun(CObject*, eSprite); ///< Fire object's gun.
	void FindClosest(const Vector2&, CObject*&, float&); ///< Find close objects.

	//IntersectLine(start, end)
	std::vector<CObject*> IntersectLine(const Vector2&, const Vector2&); ///< Find objects intersecting a line.
	
	/// <summary>
	/// Builds the input for all objects
	/// </summary>
	void BuildInput();

	/// <summary>
	/// Simulates all the objects in the game
	/// </summary>
	void Simulate();

	//Extend the draw method
	virtual void draw() override;

	void drawEnd();
	void drawBegin();

	/// <summary>
	/// Experimental feature to draw objects in a depth order
	/// </summary>
	bool m_bDepthSort = true;

	

	void SortObjects();
	
};

#endif //__L4RC_GAME_OBJECTMANAGER_H__