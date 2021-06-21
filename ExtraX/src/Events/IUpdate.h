#pragma once
#ifndef _IUPDATE_H_
#define _IUPDATE_H_

#include <list>
#include "Event.h"
namespace XX
{
	class IUpdate : public Event<IUpdate>
	{
	public:
		IUpdate();

		virtual void Update() = 0;

		void Fun() override {}
	};

	class Updater : public EventManager<IUpdate>
	{
	public:
		virtual ~Updater() = default;

		void Update();

	private:
		Updater() = default;

		Updater(const Updater&) = delete;

		Updater& operator=(const Updater&) = delete;

		friend class ExtraX;
	};
}

#endif // !_IUPDATE_H_


