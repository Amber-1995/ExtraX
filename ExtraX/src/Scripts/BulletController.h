#pragma once
#include "../Components/Component.h"
#include "../Events/Events.h"


namespace XX
{
	class BulletController : public Component, public IUpdate
	{
	public:
		XXVector3 dir;
		float speed;

		void Update() override;
		void OnDestroy()	override;

	private:
		int _life = 200;
	};

	typedef std::shared_ptr<BulletController> BulletControllerPtr;
}