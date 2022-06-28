#include "Game/Components/Transform.h"
#include "Game/Event/IOnTransform.h"
#include "Common/Graphics.h"

namespace XX::Game
{
	using namespace DirectX;
	using namespace Math;

	void Transform::_OnTransform()
	{
		_matrix_w = _matrix_s * _matrix_r * _matrix_t;
		auto& components = GetComponents();
		for (auto& i : components)
		{
			Event::IOnTransform* t = dynamic_cast<Event::IOnTransform*>(i);
			if (t) t->OnTransform();
		}
	}

	void Transform::_OnTranslate()
	{
		_OnTransform();
		auto& components = GetComponents();
		for (auto& i : components)
		{
			Event::IOnTranslate* t = dynamic_cast<Event::IOnTranslate*>(i);
			if (t) t->OnTranslate();
		}
	
	}

	void Transform::_OnRotate()
	{
		_OnTransform();
		auto& components = GetComponents();
		for (auto& i : components)
		{
			Event::IOnRotate* t = dynamic_cast<Event::IOnRotate*>(i);
			if (t) t->OnRotate();
		}
		
	}

	void Transform::_OnScale()
	{
		_OnTransform();
		auto& components = GetComponents();
		for (auto& i : components)
		{
			Event::IOnScale* t = dynamic_cast<Event::IOnScale*>(i);
			if (t) t->OnScale();
		}
	}

	void Transform::Position::_OnUpdate()
	{
		_transform->_matrix_t = XMMatrixTranslationFromVector(_vector);
		_transform->_OnTranslate();
	}

	void Transform::Position::_SetX(const float& x)
	{
		_vector = DirectX::XMVectorSetX(_vector, x);
		_OnUpdate();
	}

	float Transform::Position::_GetX()
	{
		return DirectX::XMVectorGetX(_vector);
	}

	void Transform::Position::_SetY(const float& y)
	{
		_vector = DirectX::XMVectorSetY(_vector, y);
		_OnUpdate();
	}

	float Transform::Position::_GetY()
	{
		return DirectX::XMVectorGetY(_vector);
	}

	void Transform::Position::_SetZ(const float& z)
	{
		_vector = DirectX::XMVectorSetZ(_vector, z);
		_OnUpdate();
	}

	float Transform::Position::_GetZ()
	{
		return DirectX::XMVectorGetZ(_vector);
	}

	Transform::Position::Position(Transform* const transform) :
		_transform(transform)
	{
		_vector = XMVectorZero();
		_transform->_matrix_t = XMMatrixTranslationFromVector(_vector);
	}

	void Transform::Position::Translate(const Vector& other)
	{
		_vector += other;
		_OnUpdate();
	}

	void Transform::Position::Translate(const Math::Float3& other)
	{
		_vector += XMVectorSet(other.x, other.y, other.z, 0.0f);
		_OnUpdate();
	}

	void Transform::Position::Translate(float x, float y, float z)
	{
		_vector += DirectX::XMVectorSet(x, y, z, 0.0f);
		_OnUpdate();
	}

	Transform::Position::operator Vector()
	{
		return _vector;
	}

	Transform::Position& Transform::Position::operator=(const Position& other)
	{
		_vector = other._vector;
		_OnUpdate();
		return *this;
	}

	Transform::Position& Transform::Position::operator=(const Vector& other)
	{
		_vector = other;
		_OnUpdate();
		return *this;
	}

	Transform::Position& Transform::Position::operator=(const Math::Float3& other)
	{
		_vector = XMVectorSet(other.x, other.y, other.z, 0.0f);
		_OnUpdate();
		return *this;
	}

	Transform::Position& Transform::Position::operator+=(const Math::Vector& other)
	{
		_vector += other;
		_OnUpdate();
		return *this;

	}

	Transform::Position& Transform::Position::operator+=(const Math::Float3& other)
	{
		_vector += XMVectorSet(other.x, other.y, other.z, 0.0f);
		_OnUpdate();
		return *this;
	}

	Transform::Position& Transform::Position::operator-=(const Vector& other)
	{
		_vector -= other;
		_OnUpdate();
		return *this;
	}

	Transform::Position& Transform::Position::operator-=(const Math::Float3& other)
	{
		_vector -= XMVectorSet(other.x, other.y, other.z, 0.0f);
		_OnUpdate();
		return *this;
	}

	Transform::Position& Transform::Position::operator*=(float times)
	{
		_vector *= times;
		_OnUpdate();
		return *this;
	}

	Transform::Position& Transform::Position::operator/=(float times)
	{
		_vector /= times;
		_OnUpdate();
		return *this;
	}

	Vector Transform::Position::operator+(const Vector& other) const
	{
		return _vector + other;
	}

	Math::Vector Transform::Position::operator+(const Math::Float3& other) const
	{
		return _vector + XMVectorSet(other.x, other.y, other.z, 0.0f);
	}

	Vector Transform::Position::operator-(const Vector& other) const
	{
		return _vector - other;
	}

	Math::Vector Transform::Position::operator-(const Math::Float3& other) const
	{
		return _vector - XMVectorSet(other.x, other.y, other.z, 0.0f);
	}

	Vector Transform::Position::operator*(float times) const
	{
		return _vector * times;
	}

	Vector Transform::Position::operator/(float times) const
	{
		return _vector / times;
	}

	void Transform::Rotation::_OnUpdate()
	{
		_transform->_matrix_t = XMMatrixRotationQuaternion(_quaternion);
		_transform->_OnTranslate();
	}

	Transform::Rotation::Rotation(Transform* const transform) :
		_transform(transform)
	{
		_quaternion = XMQuaternionIdentity();
		_transform->_matrix_t = XMMatrixRotationQuaternion(_quaternion);
	}

	void Transform::Rotation::Rotate(const Vector& rotation)
	{
		Vector vec = DirectX::XMQuaternionRotationRollPitchYawFromVector(rotation);
		_quaternion = DirectX::XMQuaternionMultiply(_quaternion, vec);
	}

	void Transform::Rotation::Rotate(const Math::Float3& rotation)
	{
		Vector vec = XMVectorSet(rotation.x, rotation.y, rotation.z, 0.0f);
		vec = XMQuaternionRotationRollPitchYawFromVector(vec);
		_quaternion = DirectX::XMQuaternionMultiply(_quaternion, vec);
	}

	void Transform::Rotation::Rotate(float x, float y, float z)
	{
		Vector vec = XMVectorSet(x, y, z, 0.0f);
		vec = DirectX::XMQuaternionRotationRollPitchYawFromVector(vec);
		_quaternion = DirectX::XMQuaternionMultiply(_quaternion, vec);
	}

	Transform::Rotation::operator Math::Quaternion()
	{
		return _quaternion;
	}

	Transform::Rotation& Transform::Rotation::operator=(const Rotation& other)
	{
		_quaternion = other._quaternion;
		_OnUpdate();
		return *this;
	}

	Transform::Rotation& Transform::Rotation::operator=(const Vector& other)
	{
		_quaternion = XMQuaternionRotationRollPitchYawFromVector(other);
		_OnUpdate();
		return *this;
	}

	Transform::Rotation& Transform::Rotation::operator=(const Math::Float3& other)
	{
		_quaternion = XMQuaternionRotationRollPitchYawFromVector(XMVectorSet(other.x, other.y, other.z, 0.0f));
		_OnUpdate();
		return *this;
	}

	void Transform::Scale::_OnUpdate()
	{
		_transform->_matrix_t = XMMatrixScalingFromVector(_vector);
		_transform->_OnTranslate();
	}

	void Transform::Scale::_SetX(const float& x)
	{
		_vector = DirectX::XMVectorSetX(_vector, x);
		_OnUpdate();
	}

	float Transform::Scale::_GetX()
	{
		return DirectX::XMVectorGetX(_vector);
	}

	void Transform::Scale::_SetY(const float& y)
	{
		_vector = DirectX::XMVectorSetY(_vector, y);
		_OnUpdate();
	}

	float Transform::Scale::_GetY()
	{
		return DirectX::XMVectorGetY(_vector);
	}

	void Transform::Scale::_SetZ(const float& z)
	{
		_vector = DirectX::XMVectorSetZ(_vector, z);
		_OnUpdate();
	}

	float Transform::Scale::_GetZ()
	{
		return DirectX::XMVectorGetZ(_vector);
	}
		
	Transform::Scale::Scale(Transform* const transform) :
		_transform(transform)
	{
		_vector = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
		_transform->_matrix_t = XMMatrixScalingFromVector(_vector);
	}

	Transform::Scale::operator Math::Vector()
	{
		return _vector;
	}

	Transform::Scale& Transform::Scale::operator=(const Scale& other)
	{
		_vector = other._vector;
		_OnUpdate();
		return *this;
	}

	Transform::Scale& Transform::Scale::operator=(const Vector& other)
	{
		_vector = other;
		_OnUpdate();
		return *this;
	}

	Transform::Scale& Transform::Scale::operator=(const Math::Float3& other)
	{
		_vector = DirectX::XMVectorSet(other.x, other.y, other.z, 0.0f);
		_OnUpdate();
		return *this;
	}

	Transform::Scale& Transform::Scale::operator+=(const Math::Vector& other)
	{
		_vector += other;
		_OnUpdate();
		return *this;

	}

	Transform::Scale& Transform::Scale::operator+=(const Math::Float3& other)
	{
		_vector += DirectX::XMVectorSet(other.x, other.y, other.z, 0.0f);
		_OnUpdate();
		return *this;
	}

	Transform::Scale& Transform::Scale::operator -= (const Vector& other)
	{
		_vector -= other;
		_OnUpdate();
		return *this;
	}

	Transform::Scale& Transform::Scale::operator-=(const Math::Float3& other)
	{
		_vector -= DirectX::XMVectorSet(other.x, other.y, other.z, 0.0f);
		_OnUpdate();
		return *this;
	}

	Transform::Scale& Transform::Scale::operator *= (float times)
	{
		_vector *= times;
		_OnUpdate();
		return *this;
	}

	Transform::Scale& Transform::Scale::operator /= (float times)
	{
		_vector /= times;
		_OnUpdate();
		return *this;
	}

	Vector Transform::Scale::operator+(const Vector& other) const
	{
		return _vector + other;
	}

	Vector Transform::Scale::operator+(const Math::Float3& other) const
	{
		return _vector + XMVectorSet(other.x, other.y, other.z, 0.0f);
	}

	Vector Transform::Scale::operator-(const Vector& other) const
	{
		return _vector - other;
	}

	Vector Transform::Scale::operator-(const Math::Float3& other) const
	{
		return _vector - XMVectorSet(other.x, other.y, other.z, 0.0f);
	}

	Vector Transform::Scale::operator * (float times) const
	{
		return _vector * times;
	}

	Vector Transform::Scale::operator / (float times) const
	{
		return _vector / times;
	}

	Vector Transform::Right()
	{
		Vector right = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		return XMVector3Rotate(right, rotation._quaternion);
	}

	Vector Transform::Up()
	{
		Vector up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		return XMVector3Rotate(up, rotation._quaternion);
	}

	Vector Transform::Forward()
	{
		Vector forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		return XMVector3Rotate(forward, rotation._quaternion);
	}

	void Transform::LookAt(const Vector& target)
	{
		Matrix matrix = XMMatrixLookToLH(
			position._vector,
			target - position._vector,
			Up()
		);
		rotation._quaternion = XMQuaternionRotationMatrix(matrix);
		rotation._OnUpdate();
	}

	void Transform::LookAt(const Float3& target)
	{
		Matrix matrix = XMMatrixLookToLH(
			position._vector,
			XMVectorSet(target.x, target.y, target.z, 0.0f) - position._vector,
			Up()
		);
		rotation._quaternion = XMQuaternionRotationMatrix(matrix);
		rotation._OnUpdate();
	}

	void Transform::Set(size_t thread)
	{
		ExtraX::graphics->SetWorldMatrix(&_matrix_w, thread);
	}

	Matrix Transform::GetMatrix(MATRIX_TYPE matrix_type)
	{
		switch (matrix_type)
		{
		case XX::Game::MATRIX_TYPE::WORLD_MATRIX:
			return _matrix_w;
			break;
		case XX::Game::MATRIX_TYPE::TRANSLATE_MATRIX:
			return _matrix_t;
			break;
		case XX::Game::MATRIX_TYPE::ROTATE_MATRIX:
			return _matrix_r;
			break;
		case XX::Game::MATRIX_TYPE::SCALE_MATRIX:
			return _matrix_s;
			break;
		default:
			return XMMatrixIdentity();
			break;
		}
	}
}