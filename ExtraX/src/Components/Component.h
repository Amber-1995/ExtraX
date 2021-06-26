
#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "../Data/Data.h"

namespace XX
{
	class Component
	{
	/*====================�R���X�g���N�^�[�ƃf�X�g���N�^�[====================*/
	public:
		virtual ~Component() = default;
	protected:
		Component();
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;
		
	/*================================�����o�[================================*/
	public:
		GameObject* const& game_object;
		const bool& active;
	private:
		GameObject* _game_object;
		bool _active;

	/*================================���\�b�h================================*/
	public:
		void SetActive(bool active);
		void Spawn();
		void Destroy();
		template<class T = Component, class...ARGS>
		static std::shared_ptr<T> Create(ARGS...args);
		virtual void Awake() {}
		virtual void Start() {}
		virtual void OnEnable() {}
		virtual void OnDisable() {}
		virtual void OnDestroy() {}
	private:
		void _SetGameObject(GameObject* game_object);
		void _InstallEvents();
		void _UninstallEvents();

	/*================================�t�����h================================*/
		friend class GameObject;
	};

	template<class T, class ...ARGS>
	inline std::shared_ptr<T> Component::Create(ARGS ...args)
	{
		return std::shared_ptr<T>(new T(args...));
	}

}

#endif // !_COMPONENT_H_
