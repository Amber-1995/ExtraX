#include "Scene.h"
#include "../GameObjects/GameObject.h"

XX::Scene::Scene():
	game_objects(_game_objects),
	_game_objects()
{
	
}

XX::Scene::~Scene()
{
}

void XX::Scene::AddGameObject(GameObject* game_obeject)
{
	game_obeject->SetScene(this);
	_game_objects.push_back(game_obeject);
}

void XX::Scene::RemoveGameObject(GameObject* game_obeject)
{
	_game_objects.remove(game_obeject);
}
