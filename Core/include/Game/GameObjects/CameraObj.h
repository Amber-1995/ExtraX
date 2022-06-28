#ifndef CORE_OBJ_CAMERA_H
#define CORE_OBJ_CAMERA_H


#include "Game/Module.h"
#include "Game/Components/Transform.h"
#include "Game/Components/Camera.h"

namespace XX::Game::GameObjects
{
	class CameraObj : public GameObject
	{
	public:
		Components::Transform* transform = nullptr;
		Components::Camera* camera = nullptr;
		CameraObj();
	};
}





#endif // !CORE_OBJ_CAMERA_H

