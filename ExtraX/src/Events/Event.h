//#pragma once
//#ifndef _EVENT_H_
//#define _EVENT_H_
//
//#include <list>
//#include <memory>
//
//
//namespace
//{
//	template<class T>
//	class EventManager
//	{
//	private:
//		std::list<std::shared_ptr<T>> _events;
//		std::list<std::shared_ptr<T>>::iterator _current;
//		std::list<std::shared_ptr<T>>::iterator _next;
//
//		friend class Event<T>;
//	};
//
//	template<class T>
//	class Event
//	{
//	public:
//		Event(const EventManager<T>& event_manager);
//		void Addto();
//		void Remove();
//
//	private:
//		const EventManager<T>& _event_manager;
//	};
//	template<class T>
//	inline Event<T>::Event(const EventManager<T>& event_manager)
//	{
//
//	}
//	template<class T>
//	inline void Event<T>::Addto()
//	{
//		//_event_manager._events.push_front(std::dynamic_pointer_cast<T>(dynamic_cast<Component*>(this)->Get()));
//	}
//	template<class T>
//	inline void Event<T>::Remove()
//	{
//		/*if (_event_manager._next != _event_manager._i_updates.end() &&
//			this == (*_event_manager._next).get()) {
//			ExtraX::updater._next++;
//		}
//		_event_manager._events.remove_if([this](const std::shared_ptr<T>& iupdate)->bool { return iupdate.get() == this; });*/
//
//	}
//}
//
//
//
//
//
//#endif // !_EVENT_H_
