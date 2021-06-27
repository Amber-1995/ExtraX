#pragma once
#include "../Components/Component.h"
#include "../Components/Components.h"
#include "../Events/Events.h"


namespace XX
{
	class StartButton : public Component, public IUpdate
	{
		void Start()override;
		void Update() override;

	private:
		Animation2DPtr _animation2d;
	};
	typedef std::shared_ptr<StartButton> StartButtonPtr;
}
