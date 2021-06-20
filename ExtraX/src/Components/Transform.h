#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "../Data/Data.h"
#include "Component.h"


using DirectX::XMVECTOR;
using DirectX::XMMATRIX;

namespace XX
{
	class Transform : public Component
	{
	public:
		XXVector3P position;
		XXVector3P rotation;
		XXVector3P scale;

		virtual ~Transform() = default;

		XXVector3 Forward();
		XXVector3 Up();
		XXVector3 Right();

		void SetWorldMatrix();

		void SetWorldMatrix(const XMMATRIX& offset);

	private:
		XMVECTOR _position;
		XMVECTOR _rotation;
		XMVECTOR _scale;
		XMMATRIX _matrix;

		Transform();

		void _Refresh();

		friend class Component;
	};
}


#endif // !_TRANSFORM_H_
