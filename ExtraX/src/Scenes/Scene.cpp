#include "Scene.h"
#include "../GameObjects/GameObject.h"

XX::Scene::Scene():
	game_objects(_game_objects),
	_game_objects(),
	_is_awake(false)
{
	
}

XX::Scene::~Scene()
{
}

void XX::Scene::Spawn()
{
	for (GameObjectPtr g : _game_objects)
	{
		g->Spwan();
	}

	_is_awake = true;
}

void XX::Scene::Destroy()
{
	auto i = _game_objects.begin();
	auto next = std::next(i);
	auto end = _game_objects.end();

	while (i != end)
	{
		(*i)->Destroy();
		i = next;
		if (next != end) next++;
	}

	_game_objects.clear();
}

void XX::Scene::AddGameObject(GameObjectPtr game_object)
{
	game_object->SetScene(this);
	_game_objects.push_back(game_object);

	if(_is_awake){
		game_object->Spwan();
	}
}

void XX::Scene::RemoveGameObject(GameObject* game_obeject)
{
	_game_objects.remove_if([game_obeject](const GameObjectPtr& g)->bool { return g.get() == game_obeject; });
}
