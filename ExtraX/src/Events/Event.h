#pragma once
#ifndef _EVENT_H_
#define _EVENT_H_

#include <memory>
#include "../Data/Data.h"

namespace XX
{

	template<class T>
	class Event;

	template<class T>
	class EventManager
	{
	public:
		EventManager():_events(3){}

	private:
		void Add(T* event)
		{
			_events.Add(event);
		}
		void Remove(T* event)
		{
			_events.Remove(event);
		}

	protected:
		typename XXTable<T*> _events;

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

		
	private:
		static typename EventManager<T>* _event_manager;
		virtual void _ForDynamicCast() {}
	};
}





#endif // !_EVENT_H_
