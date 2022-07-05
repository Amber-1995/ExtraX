#ifndef CORE_TRANSFORM_H
#define CORE_TRANSFORM_H

#include "Common/ExtraX.h"
#include "Common/Property.h"
#include "Game/Module.h"


namespace XX::Game::Components
{
	enum class MATRIX_TYPE
	{
		WORLD_MATRIX,
		TRANSLATE_MATRIX,
		ROTATE_MATRIX,
		SCALE_MATRIX
	};

	XXAPI class Transform : public Component
	{
	private:
		Matrix _matrix_w = DirectX::XMMatrixIdentity();
		
		Matrix _matrix_t = DirectX::XMMatrixIdentity();

		Matrix _matrix_r = DirectX::XMMatrixIdentity();

		Matrix _matrix_s = DirectX::XMMatrixIdentity();
		
		void _OnTransform();

		void _OnTranslate();

		void _OnRotate();

		void _OnScale();

		class Position
		{
			friend class Transform;

		private:
			Transform* const _transform;

			Vector _vector;

			void _OnUpdate();

			void _SetX(const float& x);

			float _GetX();

			void _SetY(const float& y);

			float _GetY();

			void _SetZ(const float& z);

			float _GetZ();

		public:
			Position(Transform* const transform);

			Property<float, Position, &_SetX, &_GetX> x = { this };

			Property<float, Position, &_SetY, &_GetY> y = { this };

			Property<float, Position, &_SetZ, &_GetZ> z = { this };

			void Translate(const Vector& other);

			void Translate(const Float3& other);

			void Translate(float x, float y, float z);

			operator Vector();

			Position& operator = (const Position& other);

			Position& operator = (const Vector& other);
			
			Position& operator = (const Float3& other);

			Position& operator += (const Vector& other);

			Position& operator += (const Float3& other);

			Position& operator -= (const Vector& other);

			Position& operator -= (const Float3& other);

			Position& operator *= (float times);

			Position& operator /= (float times);

			Vector operator + (const Vector& other) const;

			Vector operator + (const Float3& other) const;

			Vector operator - (const Vector& other) const;

			Vector operator - (const Float3& other) const;

			Vector operator * (float times) const;

			Vector operator / (float times) const;

		};

		class Rotation
		{
			friend class Transform;

		private:
			Transform* const _transform;

			Quaternion _quaternion;

			void _OnUpdate();

		public:
			Rotation(Transform* const transform);

			void Rotate(const Vector& rotation);

			void Rotate(const Float3& rotation);

			void Rotate(float x, float y, float z);

			operator Quaternion();

			Rotation& operator=(const Rotation& other);

			Rotation& operator=(const Vector& other);

			Rotation& operator=(const Float3& other);
		};

		class Scale
		{
			friend class Transform;

		private:
			Transform* const _transform;

			Vector _vector;

			void _OnUpdate();

			void _SetX(const float& x);

			float _GetX();

			void _SetY(const float& y);

			float _GetY();

			void _SetZ(const float& z);

			float _GetZ();

		public:
			Scale(Transform* const transform);

			Property<float, Scale, &_SetX, &_GetX> x = { this };

			Property<float, Scale, &_SetY, &_GetY> y = { this };

			Property<float, Scale, &_SetZ, &_GetZ> z = { this };

			operator Vector();

			Scale& operator=(const Scale& other);

			Scale& operator=(const Vector& other);

			Scale& operator=(const Float3& other);

			Scale& operator += (const Vector& other);

			Scale& operator += (const Float3& other);

			Scale& operator -= (const Vector& other);

			Scale& operator -= (const Float3& other);

			Scale& operator *= (float times);

			Scale& operator /= (float times);

			Vector operator + (const Vector& other) const;

			Vector operator + (const Float3& other) const;

			Vector operator - (const Vector& other) const;

			Vector operator - (const Float3& other) const;

			Vector operator * (float times) const;

			Vector operator / (float times) const;
		};

	public:
		Position position = { this };

		Rotation rotation = { this };

		Scale scale = { this };

		Vector Right();

		Vector Up();

		Vector Forward();

		void LookAt(const Vector& target);
						  
		void LookAt(const Float3& target);

		void Set(size_t thread);

		Matrix GetMatrix(MATRIX_TYPE matrix_type);
	};

}


#endif // !CORE_TRANSFORM_HPP
