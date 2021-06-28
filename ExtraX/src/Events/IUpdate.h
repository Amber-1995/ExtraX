#pragma once
#ifndef _IUPDATE_H_
#define _IUPDATE_H_

#include <list>
#include <thread>
#include "Event.h"
namespace XX
{
	class IUpdate : public Event<IUpdate>
	{
	public:
		virtual void Update() = 0;
	};

	class Updater : public EventManager<IUpdate>
	{
	public:
		virtual ~Updater() = default;

		void Update();

	private:

		int _num_of_processors; 
		std::atomic<UINT> _start_symble;
		UINT _start_mask;
		std::thread** _update_thread;
		void _Update(int num);

		Updater();
		Updater(const Updater&) = delete;
		Updater& operator=(const Updater&) = delete;
		

		friend class ExtraX;
	};
}

#endif // !_IUPDATE_H_


