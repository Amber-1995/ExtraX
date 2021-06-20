#pragma once
#include "../Components/Component.h"
#include "../Events/Events.h"


namespace XX
{
	class PlayerController : public Component, public IUpdate
	{
		void Update() override;
	};
	typedef std::shared_ptr<PlayerController> PlayerControllerPtr;
}