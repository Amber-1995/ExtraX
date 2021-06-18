#include "Transform.h"
#include "../XX.h"

XX::Transform::Transform() :
	position(_position, [this]() {_Refresh(); }, 0, 0, 0),
	rotation(_rotation, [this]() {_Refresh(); }, 0, 0, 0),
	scale(_scale, [this]() {_Refresh(); }, 1, 1, 1),
	_matrix(DirectX::XMMatrixIdentity())
{

}

XX::XXVector3 XX::Transform::Forward()
{
	DirectX::XMFLOAT3 uint(0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR vunit = DirectX::XMLoadFloat3(&uint);
	DirectX::XMVECTOR rq = DirectX::XMQuaternionRotationRollPitchYawFromVector(_rotation);
	DirectX::XMVECTOR ret = DirectX::XMVector3Rotate(vunit, rq);
	ret = DirectX::XMVector3Normalize(ret);
	DirectX::XMStoreFloat3(&uint,ret);

	return XXVector3(uint.x, uint.y, uint.z	);
}

XX::XXVector3 XX::Transform::Up()
{
	DirectX::XMFLOAT3 uint(0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR vunit = DirectX::XMLoadFloat3(&uint);
	DirectX::XMVECTOR rq = DirectX::XMQuaternionRotationRollPitchYawFromVector(_rotation);
	DirectX::XMVECTOR ret = DirectX::XMVector3Rotate(vunit, rq);
	ret = DirectX::XMVector3Normalize(ret);
	DirectX::XMStoreFloat3(&uint, ret);

	return XXVector3(uint.x, uint.y, uint.z);
}

XX::XXVector3 XX::Transform::Right()
{
	DirectX::XMFLOAT3 uint(1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR vunit = DirectX::XMLoadFloat3(&uint);
	DirectX::XMVECTOR rq = DirectX::XMQuaternionRotationRollPitchYawFromVector(_rotation);
	DirectX::XMVECTOR ret = DirectX::XMVector3Rotate(vunit, rq);
	ret = DirectX::XMVector3Normalize(ret);
	DirectX::XMStoreFloat3(&uint, ret);

	return XXVector3(uint.x, uint.y, uint.z);
}

void XX::Transform::SetMatrix()
{
	ExtraX::graphics.SetWorldMatrix(_matrix);
}

void XX::Transform::_Refresh()
{
	DirectX::XMMATRIX t = DirectX::XMMatrixTranslationFromVector(_position);
	DirectX::XMMATRIX r = DirectX::XMMatrixRotationRollPitchYawFromVector(_rotation);
	DirectX::XMMATRIX s = DirectX::XMMatrixScalingFromVector(_scale);

	_matrix = s * r * t;
}
