#ifndef CORE_TRANSFORM_H
#define CORE_TRANSFORM_H

#include "Common/ExtraX.h"
#include "Common/Math.h"
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
		Math::Matrix _matrix_w = DirectX::XMMatrixIdentity();
		
		Math::Matrix _matrix_t = DirectX::XMMatrixIdentity();

		Math::Matrix _matrix_r = DirectX::XMMatrixIdentity();

		Math::Matrix _matrix_s = DirectX::XMMatrixIdentity();
		
		void _OnTransform();

		void _OnTranslate();

		void _OnRotate();

		void _OnScale();

		class Position
		{
			friend class Transform;

		private:
			Transform* const _transform;

			Math::Vector _vector;

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

			void Translate(const Math::Vector& other);

			void Translate(const Math::Float3& other);

			void Translate(float x, float y, float z);

			operator Math::Vector();

			Position& operator = (const Position& other);

			Position& operator = (const Math::Vector& other);
			
			Position& operator = (const Math::Float3& other);

			Position& operator += (const Math::Vector& other);

			Position& operator += (const Math::Float3& other);

			Position& operator -= (const Math::Vector& other);

			Position& operator -= (const Math::Float3& other);

			Position& operator *= (float times);

			Position& operator /= (float times);

			Math::Vector operator + (const Math::Vector& other) const;

			Math::Vector operator + (const Math::Float3& other) const;

			Math::Vector operator - (const Math::Vector& other) const;

			Math::Vector operator - (const Math::Float3& other) const;

			Math::Vector operator * (float times) const;

			Math::Vector operator / (float times) const;

		};

		class Rotation
		{
			friend class Transform;

		private:
			Transform* const _transform;

			Math::Quaternion _quaternion;

			void _OnUpdate();

		public:
			Rotation(Transform* const transform);

			void Rotate(const Math::Vector& rotation);

			void Rotate(const Math::Float3& rotation);

			void Rotate(float x, float y, float z);

			operator Math::Quaternion();

			Rotation& operator=(const Rotation& other);

			Rotation& operator=(const Math::Vector& other);

			Rotation& operator=(const Math::Float3& other);
		};

		class Scale
		{
			friend class Transform;

		private:
			Transform* const _transform;

			Math::Vector _vector;

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

			operator Math::Vector();

			Scale& operator=(const Scale& other);

			Scale& operator=(const Math::Vector& other);

			Scale& operator=(const Math::Float3& other);

			Scale& operator += (const Math::Vector& other);

			Scale& operator += (const Math::Float3& other);

			Scale& operator -= (const Math::Vector& other);

			Scale& operator -= (const Math::Float3& other);

			Scale& operator *= (float times);

			Scale& operator /= (float times);

			Math::Vector operator + (const Math::Vector& other) const;

			Math::Vector operator + (const Math::Float3& other) const;

			Math::Vector operator - (const Math::Vector& other) const;

			Math::Vector operator - (const Math::Float3& other) const;

			Math::Vector operator * (float times) const;

			Math::Vector operator / (float times) const;
		};

	public:
		Position position = { this };

		Rotation rotation = { this };

		Scale scale = { this };

		Math::Vector Right();

		Math::Vector Up();

		Math::Vector Forward();

		void LookAt(const Math::Vector& target);

		void LookAt(const Math::Float3& target);

		void Set(size_t thread);

		Math::Matrix GetMatrix(MATRIX_TYPE matrix_type);
	};

}


#endif // !CORE_TRANSFORM_HPP
