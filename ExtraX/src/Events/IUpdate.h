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
		virtual ~IUpdate() = default;
	};
	typedef std::shared_ptr<IUpdate> IUpdatePtr;


	class Updater
	{
	public:
		void Update();

		virtual ~Updater();

	private:
		std::list<IUpdatePtr> _i_updates;
		std::list<IUpdatePtr>::iterator _current;
		std::list<IUpdatePtr>::iterator _next;

		Updater();

		Updater(const Updater&) = delete;

		Updater& operator=(const Updater&) = delete;

		friend class IUpdate;
		friend class ExtraX;
	};
}

#endif // !_IUPDATE_H_


