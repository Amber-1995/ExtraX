#include "IUpdate.h"
#include "../XX.h"
#include "../Components/Component.h"

void XX::IUpdate::Init()
{
	ExtraX::updater._i_updates.push_back(this);
}

void XX::IUpdate::Uninit()
{
	auto i = ExtraX::updater._i_updates.begin();
	auto end = ExtraX::updater._i_updates.end();
	for (i; i != end; i++) {
		if (*i == this){
			ExtraX::updater._i_updates.erase(i);
			break;
		}
	}
}

void XX::Updater::Update()
{
	auto i = _i_updates.begin();
	auto end = _i_updates.end();
	for (i; i != end; i++) {
		(*i)->Update();
	}
	i = _i_updates.begin();
	end = _i_updates.end();
	while (i != end) {
		Component* c = dynamic_cast<Component*>(*i);
		if (c->deleted) {
			_i_updates.erase(i++);
			break;
		}
		else{
			i++;
		}
	}
}

XX::Updater::~Updater()
{
}

XX::Updater::Updater():
	_i_updates(0)
{
	_i_updates.reserve(1024);
}
