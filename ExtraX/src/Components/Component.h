
#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "../Data/Data.h"

namespace XX
{
	class Component
	{
	public:
		GameObject* const& game_object;

		const bool& active;

		Component();
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;
	
		void SetActive(bool active);

		void Awake();

		void Destroy();

		template<class T = Component, class...ARGS>
		static std::shared_ptr<T> Create(ARGS...args);

	private:
		GameObject* _game_object;

		bool _active;

		void SetGameObject(GameObject* game_object);

		void _InstallEvents();

		void _UninstallEvents();

		virtual void _ForDynamicCast(){}

		friend class GameObject;
	};



	template<class T, class ...ARGS>
	inline std::shared_ptr<T> Component::Create(ARGS ...args)
	{
		return std::shared_ptr<T>(new T(args...));
	}

}

#endif // !_COMPONENT_H_
