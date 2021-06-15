#pragma once
#include "../Components/Component.h"
#include "../Events/IUpdate.h"


namespace XX
{
	class PlayerController : public Component, public IUpdate
	{
		void Update() override;
	};
}