
#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "../Data/ExtraXType.h"

namespace XX
{
	class Component
	{
	friend class GameObject;

	public:
		GameObject* const& game_object;

		const bool& active;

		Component();

		Component(const Component&) = delete;

		Component& operator=(const Component&) = delete;

		virtual ~Component();

		void SetActive(bool& active);

		void SetActive(bool&& active);

		void Destroy();

	private:
		GameObject* _game_object;

		bool _active;

		void SetGameObject(GameObject* game_object);

		void InstallEvents();

		void UninstallEvents();
	};
}

#endif // !_COMPONENT_H_
