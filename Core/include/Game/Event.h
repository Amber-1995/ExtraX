#ifndef CORE_EVENT_H
#define CORE_EVENT_H
#include"Common/ExtraX.h"



namespace XX::Game
{
	class Component;
}

namespace XX::Game::Event
{
	template<class T>
	class Event;

	template<class T>
	class EventManager
	{
	protected:
		std::list<T*> _events_list;
	public:
		void Add(Component* component)
		{
			T* t = dynamic_cast<T*>(component);
			if (t)
			{
				_events_list.push_front(t);
				t->_self = _events_list.begin();
				t->_events_list = &_events_list;
			}
		}
	};

	class IOnStart;

	template<>
	class Event<IOnStart>
	{
		friend class EventManager<IOnStart>;
	private:
		std::list<IOnStart*>::iterator _self;
		std::list<IOnStart*>* _events_list;
	public:
		virtual ~Event<IOnStart>() = default;
	};

	template<class T>
	class Event
	{
		friend class EventManager<T>;
	private:
		std::list<T*>::iterator _self;
		std::list<T*>* _events_list;
	public:
		virtual ~Event()
		{
			_events_list->erase(_self);
		}
	};

	class IUpdate : public Event<IUpdate>
	{
	public:
		virtual ~IUpdate() = default;

		virtual void Update() = 0;
	};

	class IRender2D : public Event<IRender2D>
	{
	public:
		virtual ~IRender2D() = default;

		virtual void Render2D(size_t thread) = 0;
	};

	class IRender3D : public Event<IRender3D>
	{
	public:
		virtual ~IRender3D() = default;

		virtual void Render3D(size_t thread) = 0;
	};

	class IOnStart : public Event<IOnStart>
	{
	public:
		virtual ~IOnStart() = default;

		virtual void OnStart() = 0;
	};

	class IOnTransform : public Event<IOnTransform>
	{
	public:
		virtual ~IOnTransform() = default;

		virtual void OnTransform() = 0;
	};

	class IOnTranslate : public Event<IOnTranslate>
	{
	public:
		virtual ~IOnTranslate() = default;

		virtual void OnTranslate() = 0;
	};

	class IOnRotate : public Event<IOnRotate>
	{
	public:
		virtual ~IOnRotate() = default;

		virtual void OnRotate() = 0;
	};

	class IOnScale : public Event<IOnScale>
	{
	public:
		virtual ~IOnScale() = default;

		virtual void OnScale() = 0;
	};

}


#endif // !CORE_EVENT_H

