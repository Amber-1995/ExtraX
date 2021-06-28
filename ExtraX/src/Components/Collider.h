#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"

namespace XX
{
	class AABB3D
	{
	protected:
		float top;
		float bottom;
		float left;
		float right;
		float front;
		float back;

	public:
		//virtual bool AABBCollided(AABB3D& other) = 0;
	};

	class Collider3D : public Component,public AABB3D
	{


	};
}

#endif //!_COLLIDER_H_
