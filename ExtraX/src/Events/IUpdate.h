#pragma once
#ifndef _IUPDATE_H_
#define _IUPDATE_H_

#include <vector>

namespace XX
{
	class IUpdate
	{
	public:
		virtual void Update() = 0;
		void Init();
		void Uninit();
	};

	class Updater
	{
	friend class IUpdate;
	friend class ExtraX;

	public:
		void Update();

		virtual ~Updater();

	private:
		std::vector<IUpdate*> _i_updates;

		Updater();

		Updater(const Updater&) = delete;

		Updater& operator=(const Updater&) = delete;
	};
}

#endif // !_IUPDATE_H_


