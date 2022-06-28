#ifndef CORE_IUPDATE_H
#define CORE_IUPDATE_H

#include "Common/ExtraX.h"

namespace XX::Game::Event
{

	class IUpdate
	{
	private:
		inline static std::list<IUpdate*> _new_list;

		inline static std::list<IUpdate*> _current_list;
		
		std::list<IUpdate*>::iterator _self;

	public:
		IUpdate();

		virtual ~IUpdate();

		virtual void Update() = 0;

		static void FramePreprocess();

		static void FrameProcess(size_t thread);
	};
}

#endif // !CORE_IUPDATE_H

