
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

		const bool& deleted;

		Component();

		Component(const Component&) = delete;

		Component& operator=(const Component&) = delete;

		virtual ~Component();

		void SetActive(bool& active);

		void SetActive(bool&& active);

		void Delete();

	private:
		GameObject* _game_object;

		bool _active;

		bool _deleted;

		void SetGameObject(GameObject* game_object);

		void InitEvents();
	};
}

#endif // !_COMPONENT_H_
