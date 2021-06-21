#pragma once
#ifndef _EVENT_H_
#define _EVENT_H_

#include <list>
#include <memory>


namespace XX
{
	template<class T>
	class EventManager;


	template<class T>
	class Event
	{
	public:
		Event(const EventManager<T>& event_manager);
		void Addto();
		void Remove();

		virtual void  Fun() = 0;

	private:
		const EventManager<T>& _event_manager;
	};


	template<class T>
	class EventManager
	{
	protected:
		typename std::template list<T*> _events;
		typename std::template list<T*>::iterator _current;
		typename std::template list<T*>::iterator _next;

		friend class Event<T>;
		friend class ExtraX;
	};

	template<class T>
	inline Event<T>::Event(const EventManager<T>& event_manager):
		_event_manager(event_manager)
	{

	}

	template<class T>
	inline void Event<T>::Addto()
	{
		_event_manager._events.push_front(this);
	}

	template<class T>
	inline void Event<T>::Remove()
	{
		if (_event_manager._next != _event_manager._events.end() &&
			this == (*_event_manager._next)) {
			//_event_manager._next++;
		}
		//_event_manager._events.remove(dynamic_cast<T*>(this));
	}

}





#endif // !_EVENT_H_
