#pragma once
#include "../Components/Component.h"
#include "../Events/IRender.h"


namespace XX
{
	class BulletController : public Component, public IRender
	{
		void Render() override;
	};
}