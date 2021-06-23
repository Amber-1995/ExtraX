#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "../Data/Data.h"
#include "Component.h"


using DirectX::XMVECTOR;
using DirectX::XMMATRIX;

namespace XX
{
	enum TRANSFORM_MATRIX
	{
		TRANSFORM_TRANSLATION_MATRIX,
		TRANSFORM_ROTATION_MATRIX,
		TRANSFORM_SCALING_MATRIX
	};

	class Transform : public Component
	{
	public:
		XXVector3P position;
		XXVector3P rotation;
		XXVector3P scale;

		XXVector3 Forward();
		XXVector3 Up();
		XXVector3 Right();

		void SetWorldMatrix();

		void SetWorldMatrix(const XMMATRIX& offset);

		XMMATRIX GetMatrix(TRANSFORM_MATRIX matrix_type);

	private:
		XMVECTOR _position;
		XMVECTOR _rotation;
		XMVECTOR _scale;

		XMMATRIX _t_matrix;
		XMMATRIX _r_matrix;
		XMMATRIX _s_matrix;
		XMMATRIX _world_matrix;

		Transform();
		Transform(const Transform&) = delete;
		Transform& operator=(const Transform&) = delete;

		void _Refresh();

		friend class Component;
	};
}


#endif // !_TRANSFORM_H_
