#include "Scene.h"
#include "../GameObjects/GameObject.h"

XX::Scene::Scene():
	game_objects(_game_objects),
	_game_objects(0)
{
	_game_objects.reserve(256);
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
	std::vector<GameObject*>::iterator i = _game_objects.begin();
	std::vector<GameObject*>::iterator end = _game_objects.end();

	for (i; i != end; i++) {
		if (*i == game_obeject){
			_game_objects.erase(i);
			break;
		}
	}
	
}
