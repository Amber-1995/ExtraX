#include "Transform.h"
#include "../XX.h"

using namespace DirectX;

XX::Transform::Transform() :
	position(_position, [this]() {_Refresh(); }, 0, 0, 0),
	rotation(_rotation, [this]() {_Refresh(); }, 0, 0, 0),
	scale(_scale, [this]() {_Refresh(); }, 1, 1, 1),
	_world_matrix(DirectX::XMMatrixIdentity()),
	_t_matrix(DirectX::XMMatrixIdentity()),
	_r_matrix(DirectX::XMMatrixIdentity()),
	_s_matrix(DirectX::XMMatrixIdentity())
{

}

XX::XXVector3 XX::Transform::Forward()
{
	XMFLOAT3 uint(0.0f, 0.0f, 1.0f);
	XMVECTOR vunit = DirectX::XMLoadFloat3(&uint);
	XMVECTOR rq = XMQuaternionRotationRollPitchYawFromVector(_rotation);
	XMVECTOR ret = XMVector3Rotate(vunit, rq);
	ret = DirectX::XMVector3Normalize(ret);
	XMStoreFloat3(&uint,ret);

	return XXVector3(uint.x, uint.y, uint.z	);
}

XX::XXVector3 XX::Transform::Up()
{

	XMFLOAT3 uint(0.0f, 1.0f, 0.0f);
	XMVECTOR vunit = XMLoadFloat3(&uint);
	XMVECTOR rq = XMQuaternionRotationRollPitchYawFromVector(_rotation);
	XMVECTOR ret = XMVector3Rotate(vunit, rq);
	ret = XMVector3Normalize(ret);
	XMStoreFloat3(&uint, ret);

	return XXVector3(uint.x, uint.y, uint.z);
}

XX::XXVector3 XX::Transform::Right()
{
	XMFLOAT3 uint(1.0f, 0.0f, 0.0f);
	XMVECTOR vunit = XMLoadFloat3(&uint);
	XMVECTOR rq = XMQuaternionRotationRollPitchYawFromVector(_rotation);
	XMVECTOR ret = XMVector3Rotate(vunit, rq);
	ret = DirectX::XMVector3Normalize(ret);
	XMStoreFloat3(&uint, ret);

	return XXVector3(uint.x, uint.y, uint.z);
}

void XX::Transform::SetWorldMatrix()
{
	ExtraX::graphics.SetWorldMatrix(_world_matrix);
}

void XX::Transform::SetWorldMatrix(const XMMATRIX& offset)
{
	ExtraX::graphics.SetWorldMatrix(offset * _world_matrix);
}

XMMATRIX XX::Transform::GetMatrix(TRANSFORM_MATRIX matrix_type)
{
	switch (matrix_type)
	{
	case TRANSFORM_TRANSLATION_MATRIX:
	{
		return _t_matrix;
		break;
	}
	case TRANSFORM_ROTATION_MATRIX:
	{
		return _r_matrix;
		break;
	}
	case TRANSFORM_SCALING_MATRIX:
	{
		return _s_matrix;
		break;
	}
	default:
	{
		return DirectX::XMMatrixIdentity();
		break;
	}
	}
	return DirectX::XMMatrixIdentity();
}

void XX::Transform::_Refresh()
{
	_t_matrix = XMMatrixTranslationFromVector(_position);
	_r_matrix = XMMatrixRotationRollPitchYawFromVector(_rotation);
	_s_matrix = XMMatrixScalingFromVector(_scale);

	_world_matrix = _s_matrix * _r_matrix * _t_matrix;
}
