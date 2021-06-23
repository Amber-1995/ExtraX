#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"


using DirectX::XMMATRIX;

namespace XX
{
	class Camera : public Component
	{
	public:
		static Camera* const& main_camera;

		void Update();

	private:
		static Camera* _main_camera;

		XMMATRIX _view_matrix;

		XMMATRIX _projection_matrix;

		Camera();
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

		friend class Component;
	};
	typedef std::shared_ptr<Camera> CameraPtr;
}

#endif // !_CAMERA_H_
