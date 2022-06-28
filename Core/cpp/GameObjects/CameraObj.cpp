#include "Game/GameObjects/CameraObj.h"



namespace XX::Game::GameObjects
{
	CameraObj::CameraObj()
	{
		transform = AddComponent<Components::Transform>();
		camera = AddComponent<Components::Camera>();
	}
}
