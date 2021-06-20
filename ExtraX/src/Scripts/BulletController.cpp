#include "BulletController.h"

#include "../Scenes/Scene.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"


void XX::BulletController::Update()
{
	game_object->transform->position += XXVector3(0.0f,0.0f,0.1f);

	if (game_object->transform->position.z > 10)
	{
		game_object->Destroy();
		return;
	}


	for (GameObjectPtr i : game_object->scene->game_objects)
	{
		XXVector3 v = game_object->transform->position - i->transform->position;
		float l = v.GetLength();
		if (l < 1) {
			if (i->tag == "enemy")
			{
				game_object->Destroy();
				i->Destroy();
				return;
				
			}
		}
	}
	
	
}
