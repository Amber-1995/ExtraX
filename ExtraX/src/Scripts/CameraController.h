#pragma once
#include "../GameObjects/GameObject.h"
#include "../Components/Component.h"
#include "../Events/Events.h"


namespace XX
{
	class CameraController : public Component, public IUpdate
	{
	public:
		GameObjectPtr target;

		void Update() override;
	};
	typedef std::shared_ptr<CameraController> CameraControllerPtr;
}