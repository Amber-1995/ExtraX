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
	_transform = new Transform();
}

XX::GameObject::~GameObject()
{

}

void XX::GameObject::SetScene(Scene* scene)
{
	_scene = scene;
	InstallComponentsEvents();
}

void XX::GameObject::InstallComponentsEvents()
{
	for (Component* c : _components)
	{
		c->InstallEvents();
	}
}

void XX::GameObject::AddComponent(Component* component)
{
	component->SetGameObject(this);
	_components.push_front(component);
}

void XX::GameObject::RemoveComponent(Component* component)
{
	_components.remove(component);

}

void XX::GameObject::Destroy()
{
	_scene->RemoveGameObject(this);

	auto i = _components.begin();
	auto end = _components.end();
	auto next = std::next(i);
	while (i!=end)
	{
		(*i)->Destroy();
		i = next;
		if (next != end)next++;
	}
	delete this;
}
