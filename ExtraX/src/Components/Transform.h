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
		XXVector3P position;
		XXVector3P rotation;
		XXVector3P scale;

		Transform();

		XXVector3 Forward();
		XXVector3 Up();
		XXVector3 Right();

		void SetMatrix();

	private:
		DirectX::XMVECTOR _position;
		DirectX::XMVECTOR _rotation;
		DirectX::XMVECTOR _scale;
		DirectX::XMMATRIX _matrix;

	

		void _Refresh();


	};
}


#endif // !_TRANSFORM_H_
