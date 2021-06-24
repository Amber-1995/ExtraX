#include "IUpdate.h"
#include "../XX.h"
#include "../Components/Component.h"
#include "../GameObjects/GameObject.h"


void XX::Updater::Update()
{
	for (int i = 0; i < _events.width; i++) {
		for (int j = 0; j < _events.length; j++) {
			if (_events.GetUnit(i, j).is_using &&
				dynamic_cast<Component*>(_events.GetUnit(i, j).data)->game_object->active &&
				dynamic_cast<Component*>(_events.GetUnit(i, j).data)->active
				){
				_events.GetUnit(i, j).data->Update();
			}
		}
	}

}


