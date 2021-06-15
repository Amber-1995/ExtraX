#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "../Data/ExtraXType.h"
#include <vector>
#include <string>
namespace XX
{
	class GameObject
	{
	friend class Scene;

	public:
		std::string tag;

		std::string name;

		Scene* const& scene;

		Transform*& transform;

		std::vector<Component*> const& components;

		GameObject();

		GameObject(const GameObject&) = delete;

		GameObject& operator=(const GameObject&) = delete;

		virtual ~GameObject();

		void AddComponent(Component* component);

		void RemoveComponent(Component* component);

		void Destroy();

	private:
		Scene* _scene;

		Transform* _transform;

		std::vector<Component*> _components;

		void SetScene(Scene* scene);

	};
}




#endif // !_GAMEOBJECT_H_
