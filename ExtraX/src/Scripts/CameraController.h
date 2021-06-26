#pragma once
#include "../GameObjects/GameObject.h"
#include "../Components/Component.h"
#include "../Events/Events.h"


namespace XX
{
	class CameraController : public Component, public IUpdate
	{
	public:
		void Update() override;
		void Start() override;
	};
	typedef std::shared_ptr<CameraController> CameraControllerPtr;
}