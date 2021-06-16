#pragma once
#ifndef _IUPDATE_H_
#define _IUPDATE_H_

#include <list>

namespace XX
{
	class IUpdate
	{
	public:
		virtual void Update() = 0;
		void Addto();
		void Remove();
	};

	class Updater
	{
	friend class IUpdate;
	friend class ExtraX;

	public:
		void Update();

		virtual ~Updater();

	private:
		std::list<IUpdate*> _i_updates;
		std::list<IUpdate*>::iterator _current;
		std::list<IUpdate*>::iterator _next;

		Updater();

		Updater(const Updater&) = delete;

		Updater& operator=(const Updater&) = delete;
	};
}

#endif // !_IUPDATE_H_


