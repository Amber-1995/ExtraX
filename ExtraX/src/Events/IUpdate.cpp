#include "IUpdate.h"
#include "../XX.h"
#include "../Components/Component.h"



void XX::Updater::Update()
{
	_current = _events.begin();
	_next = std::next(_current);
	auto end = _events.end();
	while (_current != end)
	{
		(*_current)->Update();
		_current = _next;
		if (_next != end)_next++;
	}

}


