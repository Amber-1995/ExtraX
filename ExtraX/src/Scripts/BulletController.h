#pragma once
#include "../Components/Component.h"
#include "../Events/Events.h"


namespace XX
{
	class BulletController : public Component, public IUpdate
	{
		void Update() override;
	};
}