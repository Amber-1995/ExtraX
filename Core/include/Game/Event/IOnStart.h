#ifndef CORE_IONSTART_H
#define CORE_IONSTART_H


#include "Common/ExtraX.h"


namespace XX::Game::Event
{
	class IOnStart
	{
	public:
		virtual ~IOnStart() = default;

		virtual void OnStart() = 0;
	};
}



#endif // !CORE_IONSTART_H
