#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "../Data/Data.h"
#include <list>
#include <string>
namespace XX
{
	class GameObject
	{
	public:
		std::string tag;

		std::string name;

		const bool& active;

		Scene* const& scene;

		TransformPtr const& transform;

		std::list<ComponentPtr> const& components;

		GameObject(const GameObject&) = delete;

		GameObject& operator=(const GameObject&) = delete;

		virtual ~GameObject();

		template<class T>
		std::shared_ptr<T> GetComponent();

		void SetActive(bool active);

		void AddComponent(ComponentPtr component);

		void RemoveComponent(Component* component);

		void Spwan();

		void Destroy();

		template<class T = GameObject, class ...ARGS>
		static GameObjectPtr Create(ARGS ...args);

	private:
		bool _active;

		Scene* _scene;

		TransformPtr _transform;

		std::list<ComponentPtr> _components;

		GameObject();

		void SetScene(Scene* scene);


		friend class Scene;
		friend class Component;
	};

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponent()
	{
		for (auto& c : _components){

			if (dynamic_cast<T*>(c.get())) {
				return std::dynamic_pointer_cast<T>(c);
			}
		}
		return std::shared_ptr<T>();
	}

	template<class T, class ...ARGS>
	inline GameObjectPtr GameObject::Create(ARGS ...args)
	{
		return GameObjectPtr(new T(args...));
	}
}




#endif // !_GAMEOBJECT_H_
