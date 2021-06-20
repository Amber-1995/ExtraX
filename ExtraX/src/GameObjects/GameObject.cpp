#include "GameObject.h"
#include "../Components/Component.h"
#include "../Components/Transform.h"
#include "../Scenes/Scene.h"

XX::GameObject::GameObject() :
	tag("default"),
	name("default"),
	scene(_scene),
	transform(_transform),
	components(_components),
	_scene(nullptr),
	_transform(),
	_components()
{
	_transform = Component::Create<Transform>();
}

XX::GameObject::~GameObject()
{

}

void XX::GameObject::SetScene(Scene* scene)
{
	_scene = scene;
}

XX::GameObjectPtr XX::GameObject::_Get()
{
	auto i = _scene->game_objects.begin();
	auto end = _scene->game_objects.end();
	for (i; i != end; i++) {
		if ((*i).get() == this) {
			return *i;
		}
	}

	return GameObjectPtr();
}



void XX::GameObject::AddComponent(ComponentPtr component)
{
	component->SetGameObject(this);

	_components.push_front(component);

}

void XX::GameObject::RemoveComponent(Component* component)
{
	_components.remove_if([component](const ComponentPtr& g)->bool { return g.get() == component; });
}

void XX::GameObject::Awake()
{
	for (ComponentPtr c : _components)
	{
		c->Awake();
	}
}

void XX::GameObject::Destroy()
{
	auto i = _components.begin();
	auto next = std::next(i);
	auto end = _components.end();

	while (i != end)
	{
		(*i)->Destroy();
		i = next;
		if (next != end) next++;
	}

	_components.clear();

	_scene->RemoveGameObject(this);

}
