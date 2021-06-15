#include "BulletController.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"
#include "../Scenes/Scene.h"

void XX::BulletController::Render()
{
	game_object->transform->position.z += 0.1f;

	if (game_object->transform->position.z > 10)
	{
		game_object->Destroy();
	}

	auto i = game_object->scene->game_objects.begin();
	auto end = game_object->scene->game_objects.end();

	for (i; i != end; i++)
	{
		auto v = game_object->transform->position - (*i)->transform->position;;
		auto l = D3DXVec3Length(&v);
		if (l < 1) {
			if ((*i)->tag == "enemy")
			{
				game_object->Destroy();
				(*i)->Destroy();
				break;
				
			}
		}
	}
	
	
}
