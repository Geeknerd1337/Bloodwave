/// \file Helpers.h
/// \brief Interface for helper functions.

#ifndef __L4RC_GAME_HELPERS_H__
#define __L4RC_GAME_HELPERS_H__

#include "GameDefines.h"

const Vector2 AngleToVector(const float theta); ///< Convert angle to vector.
const Vector2 VectorNormalCC(const Vector2& v); ///< Counterclockwise normal.
const Vector2 RotateVector(const Vector2&, float); ///< Rotate a vector.
void NormalizeAngle(float& theta); ///< Normalize angle to \f$\pm\pi\f$.
float Lerp(float, float, float);

/// <summary>
/// Allows us to see if one type is an instance of another.
/// </summary>
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}



#endif //__L4RC_GAME_HELPERS_H__