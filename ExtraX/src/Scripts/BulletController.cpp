#include "BulletController.h"

#include "../Scenes/Scene.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"


void XX::BulletController::Update()
{
	game_object->transform->position += XXVector3(0.0f,0.0f,0.1f);

	if (game_object->transform->position.z > 10)
	{
		auto explosion = GameObject::Create();
		{
			explosion->transform->position = game_object->transform->position;
			auto s = Component::Create<Billboard>(5.0f, 5.0f, "Assets\\Textures\\transparent.png");
			explosion->AddComponent(s);

			auto a = Component::Create<Animation2D>();
			a->SetTarget(s);
			a->AddAnimationClip("Assets\\Textures\\explosion.png", 4, 4, "explosion", 0, 15, true, "explosion");
			a->SetEnterAnimation("explosion");
			a->AddAnimationEvent("explosion", 15, [a](){a->game_object->Destroy(); });
			explosion->AddComponent(a);
		}
		game_object->scene->AddGameObject(explosion);
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

				auto explosion = GameObject::Create();
				{
					explosion->transform->position = game_object->transform->position;
					auto s = Component::Create<Billboard>(5.0f, 5.0f, "Assets\\Textures\\transparent.png");
					explosion->AddComponent(s);

					auto a = Component::Create<Animation2D>();
					a->SetTarget(s);
					a->AddAnimationClip("Assets\\Textures\\explosion.png", 4, 4, "explosion", 0, 15, true, "explosion");
					a->SetEnterAnimation("explosion");
					a->AddAnimationEvent("explosion", 15, [a]() {a->game_object->Destroy(); });
					explosion->AddComponent(a);
				}
				game_object->scene->AddGameObject(explosion);


				game_object->Destroy();
				i->Destroy();
				return;
				
			}
		}
	}
	
	
}
