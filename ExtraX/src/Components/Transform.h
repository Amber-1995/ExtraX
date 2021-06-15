#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "../Data/ExtraXType.h"
#include "Component.h"

namespace XX
{
	class Transform : public Component
	{
	public:
		D3DXVECTOR3 position;
		D3DXVECTOR3 rotation;
		D3DXVECTOR3 scale;

		Transform();

	};
}


#endif // !_TRANSFORM_H_
