#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"
#include "../Events/IUpdate.h"
#include <DirectXMath.h>

namespace XX
{
	class Camera : public Component
	{
	public:
		static Camera* const& main_camera;

		Camera();

		virtual ~Camera();

		void Update();

	private:
		static Camera* _main_camera;

		DirectX::XMMATRIX _view_matrix;
		DirectX::XMMATRIX _projection_matrix;
	};
}

#endif // !_CAMERA_H_
