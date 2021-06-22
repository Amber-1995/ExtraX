#pragma once
#include "../Components/Component.h"
#include "../Events/Events.h"


namespace XX
{
	class CameraController : public Component, public IUpdate
	{
		void Update() override;
	};
	typedef std::shared_ptr<CameraController> CameraControllerPtr;
}