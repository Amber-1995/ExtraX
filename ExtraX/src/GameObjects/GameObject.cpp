#include "GameObject.h"
#include "../Components/Component.h"
#include "../Components/Transform.h"
#include "../Scenes/Scene.h"

XX::GameObject::GameObject() :
	tag(""),
	name(""),
	scene(_scene),
	transform(_transform),
	components(_components),
	_scene(nullptr),
	_transform(),
	_components(0)
{
	_components.reserve(256);
	_transform = new Transform();
}

XX::GameObject::~GameObject()
{

}

void XX::GameObject::SetScene(Scene* scene)
{
	_scene = scene;
}

void XX::GameObject::AddComponent(Component* component)
{
	component->SetGameObject(this);
	component->InitEvents();
	_components.push_back(component);
}

void XX::GameObject::RemoveComponent(Component* component)
{
	std::vector<Component*>::iterator i = _components.begin();
	std::vector<Component*>::iterator end = _components.end();

	for (i; i != end; i++)
	{
		if (*i == component) {
			_components.erase(i);
			break;
		}
	}

}

void XX::GameObject::Destroy()
{
	_scene->RemoveGameObject(this);
	auto i = _components.begin();
	auto end = _components.end();
	for (i; i != end; i++){
		(*i)->Delete();
	}
}
