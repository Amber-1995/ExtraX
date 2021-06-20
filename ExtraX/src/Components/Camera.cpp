#include "Camera.h"
#include "../XX.h"
#include "Transform.h"
#include "../GameObjects/GameObject.h"


using namespace DirectX;


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



void XX::Camera::Update()
{
	XMFLOAT3 e = game_object->transform->position;
	XMVECTOR eye = DirectX::XMLoadFloat3(&e);
	XMFLOAT3 f = game_object->transform->position + game_object->transform->Forward();
	XMVECTOR focus = DirectX::XMLoadFloat3(&f);
	XMFLOAT3 u(0.0f, 1.0f, 0.0f);
	XMVECTOR up = DirectX::XMLoadFloat3(&u);

	_view_matrix = DirectX::XMMatrixLookAtLH(
		eye,
		focus,
		up
	);
	ExtraX::graphics.SetViewMatrix(_view_matrix);

	ExtraX::graphics.SetProjectionMatrix(_projection_matrix);
}
