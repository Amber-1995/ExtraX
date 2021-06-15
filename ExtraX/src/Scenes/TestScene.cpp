#include "TestScene.h"
#include "../Scripts/Scripts.h"

XX::TestScene::TestScene()
{
	GameObject* camera = new GameObject();
	{
		Camera* c = new Camera();
		camera->AddComponent(c);
	}
	AddGameObject(camera);

	GameObject* p2d = new GameObject();
	{
		Sprite* s = new Sprite();
		p2d->AddComponent(s);
	}
	AddGameObject(p2d);


	GameObject* field = new GameObject();
	{

		Field* f = new Field();
		field->AddComponent(f);
	}
	AddGameObject(field);

	GameObject* player = new GameObject();
	{
		player->tag = "player";
		player->transform->position.z -= 5;
		Model* m = new Model("Assets\\models\\torus\\torus.obj");
		player->AddComponent(m);

		PlayerController* pc = new PlayerController();
		player->AddComponent(pc);
	}
	AddGameObject(player);

	GameObject* enemy1 = new GameObject();
	{
		enemy1->tag = "enemy";
		enemy1->transform->position.z += 5;
		Model* m = new Model("Assets\\models\\torus\\torus.obj");
		enemy1->AddComponent(m);
	}
	AddGameObject(enemy1);

	GameObject* enemy2 = new GameObject();
	{
		enemy2->tag = "enemy";
		enemy2->transform->position.z += 5;
		enemy2->transform->position.x += 5;
		Model* m = new Model("Assets\\models\\torus\\torus.obj");
		enemy2->AddComponent(m);
	}
	AddGameObject(enemy2);

	GameObject* enemy3 = new GameObject();
	{
		enemy3->tag = "enemy";
		enemy3->transform->position.z += 5;
		enemy3->transform->position.x -= 5;
		Model* m = new Model("Assets\\models\\torus\\torus.obj");
		enemy3->AddComponent(m);
	}
	AddGameObject(enemy3);
}
