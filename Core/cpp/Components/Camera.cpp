#include "Game/Components/Camera.h"
#include "Common/Graphics.h"


namespace XX::Game::Components
{
	using namespace DirectX;

	void Camera::OnStart()
	{
		_transform = GetComponent<Transform>();

		Vector eye = _transform->position;
		Vector focus = eye + _transform->Forward();
		Vector up = _transform->Up();
		_view_matrix = DirectX::XMMatrixLookAtLH(eye,focus,up);

		_projection_matrix = DirectX::XMMatrixPerspectiveFovLH(1.0f, ExtraX::graphics->width / ExtraX::graphics->height, 1.0f, 5000.0f);
	}

	void Camera::OnTransform()
	{
		Vector eye = _transform->position;
		Vector focus = eye + _transform->Forward();
		Vector up = _transform->Up();
		_view_matrix = DirectX::XMMatrixLookAtLH(eye, focus, up);

		_projection_matrix = DirectX::XMMatrixPerspectiveFovLH(1.0f, ExtraX::graphics->width / ExtraX::graphics->height, 1.0f, 5000.0f);
	}

	void Camera::Set(size_t thread)
	{
		if (_main_camera)
		{
			ExtraX::graphics->SetViewMatrix(&_main_camera->_view_matrix, thread);
			ExtraX::graphics->SetProjectionMatrix(&_main_camera->_projection_matrix, thread);
		}
		
	}

	Camera::Camera()
	{
		if (!_main_camera) _main_camera = this;
	}

	void Camera::SetMainCamera()
	{
		_main_camera = this;
	}


}
