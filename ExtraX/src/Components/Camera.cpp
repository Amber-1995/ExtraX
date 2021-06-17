#include "Camera.h"
#include "../XX.h"

XX::Camera* const& XX::Camera::main_camera = _main_camera;
XX::Camera* XX::Camera::_main_camera = nullptr;

XX::Camera::Camera()
{
	_main_camera = this;
}

XX::Camera::~Camera()
{
}

void XX::Camera::Update() const
{
	D3DXMATRIX view_matrix;
	D3DXVECTOR3 position(0, 10, -12);
	D3DXVECTOR3 target(0, 0, 0);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(
		&view_matrix,
		&position,
		&target,
		&up
	);

	ExtraX::graphics.SetViewMatrix(&view_matrix);

	D3DXMATRIX projection_matrix;
	D3DXMatrixPerspectiveFovLH(&projection_matrix, 1.0f, (float)960 / 540, 1.0f, 1000.0f);
	ExtraX::graphics.SetProjectionMatrix(&projection_matrix);

}
