#pragma once
#ifndef _EVENT_H_
#define _EVENT_H_

#include <list>
#include <memory>

namespace XX
{

	template<class T>
	class Event;

	template<class T>
	class EventManager
	{
	private:
		void Add(T* event)
		{
			_events.push_back(event);
		}
		void Remove(T* event)
		{
			if (_next != _events.end() &&
				event == (*_next)) {
				_next++;
			}
			_events.remove(event);
		}

	protected:
		typename std::list<T*> _events;
		typename std::list<T*>::iterator _current;
		typename std::list<T*>::iterator _next;

		friend class Event<T>;
	};

	template<class T>
	class Event
	{
	public:
		void Addto()
		{
			_event_manager->Add(dynamic_cast<T*>(this));
		}

		void Remove()
		{
			_event_manager->Remove(dynamic_cast<T*>(this));
		}

		virtual void Fun() = 0;
	private:
		static typename EventManager<T>* _event_manager;
	};
}





#endif // !_EVENT_H_
