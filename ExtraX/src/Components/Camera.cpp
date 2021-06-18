#include "Camera.h"
#include "../XX.h"
#include "Transform.h"
#include "../GameObjects/GameObject.h"

XX::Camera* const& XX::Camera::main_camera = _main_camera;
XX::Camera* XX::Camera::_main_camera = nullptr;

XX::Camera::Camera()
{
	_main_camera = !_main_camera ? this : _main_camera;

	_view_matrix = DirectX::XMMatrixIdentity();

	float w = (float)ExtraX::graphics.width;
	float h = (float)ExtraX::graphics.height;
	_projection_matrix = DirectX::XMMatrixPerspectiveFovLH(1.0f, w / h, 1.0f, 5000.0f);
}

XX::Camera::~Camera()
{
}

void XX::Camera::Update()
{
	DirectX::XMFLOAT3 e = game_object->transform->position;
	DirectX::XMVECTOR eye = DirectX::XMLoadFloat3(&e);
	DirectX::XMFLOAT3 f = game_object->transform->position + game_object->transform->Forward();
	DirectX::XMVECTOR focus = DirectX::XMLoadFloat3(&f);
	DirectX::XMFLOAT3 u(0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&u);

	_view_matrix = DirectX::XMMatrixLookAtLH(
		eye,
		focus,
		up
	);
	ExtraX::graphics.SetViewMatrix(_view_matrix);

	ExtraX::graphics.SetProjectionMatrix(_projection_matrix);
}
