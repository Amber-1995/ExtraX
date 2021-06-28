#include "IUpdate.h"
#include "../XX.h"
#include "../Components/Component.h"
#include "../GameObjects/GameObject.h"


void XX::Updater::Update()
{
	_start_symble = _start_mask;
	while (_start_symble & _start_mask)
	{
		std::this_thread::yield();	
	}
}

XX::Updater::Updater()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	_num_of_processors = sysInfo.dwNumberOfProcessors;

	_start_symble = 0;
	_start_mask = 0;
	for (int i = 0; i < _num_of_processors; i++)
	{
		_start_mask = (_start_mask << 1) + 1;
	}
	_update_thread = new std::thread*[_num_of_processors];
	for (int i = 0; i < _num_of_processors; i++)
	{
		_update_thread[i] = new std::thread([this](int i) {_Update(i); }, i);
	}
}

void XX::Updater::_Update(int num)
{
	UINT mask = 1;
	mask = mask << num;
	while (1)
	{
		while (!(_start_symble & mask))
		{
			std::this_thread::yield();
		}

		for (int i = 0; i < _events.width; i++) {
			for (int j = num; j < _events.length; j += _num_of_processors) {
				if (_events.GetUnit(i, j).is_using &&
					dynamic_cast<Component*>(_events.GetUnit(i, j).data)->game_object->active &&
					dynamic_cast<Component*>(_events.GetUnit(i, j).data)->active
					) {
					_events.GetUnit(i, j).data->Update();
				}
			}
		}

		_start_symble -= mask;
	}
	
		
	
}


