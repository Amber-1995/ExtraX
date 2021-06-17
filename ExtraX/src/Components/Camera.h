#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"
#include "../Events/IUpdate.h"

namespace XX
{
	class Camera : public Component
	{
	public:
		static Camera* const& main_camera;
		Camera();

		virtual ~Camera();

		void Update() const;

	private:
		static Camera* _main_camera;
	};
}

#endif // !_CAMERA_H_
