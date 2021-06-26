#include "GameObject.h"
#include "../Components/Component.h"
#include "../Components/Transform.h"
#include "../Scenes/Scene.h"

XX::GameObject::GameObject() :
	tag("default"),
	name("default"),
	active(_active),
	scene(_scene),
	transform(_transform),
	components(_components),
	_scene(nullptr),
	_transform(),
	_components(),
	_active(true)
{
	_transform = Component::Create<Transform>();
	AddComponent(_transform);
}

XX::GameObject::~GameObject()
{

}

void XX::GameObject::SetScene(Scene* scene)
{
	_scene = scene;
}

void XX::GameObject::SetActive(bool active)
{
	_active = active;
}

void XX::GameObject::AddComponent(ComponentPtr component)
{
	component->_SetGameObject(this);

	_components.push_front(component);

}

void XX::GameObject::RemoveComponent(Component* component)
{
	_components.remove_if([component](const ComponentPtr& g)->bool { return g.get() == component; });
}

void XX::GameObject::Spwan()
{
	for (ComponentPtr c : _components)
	{
		c->Spawn();
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
