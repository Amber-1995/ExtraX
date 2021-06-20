#include "IUpdate.h"
#include "../XX.h"
#include "../Components/Component.h"

void XX::IUpdate::Addto()
{
	ExtraX::updater._i_updates.push_front(std::dynamic_pointer_cast<IUpdate>(dynamic_cast<Component*>(this)->Get()));
}

void XX::IUpdate::Remove()
{
	if (ExtraX::updater._next!=ExtraX::updater._i_updates.end() &&
		this == (*ExtraX::updater._next).get()) {
		ExtraX::updater._next++;
	}
	ExtraX::updater._i_updates.remove_if([this](const IUpdatePtr& iupdate)->bool { return iupdate.get() == this; });
}

void XX::Updater::Update()
{
	_current = _i_updates.begin();
	_next = std::next(_current);
	auto end = _i_updates.end();
	while (_current != end)
	{
		(*_current)->Update();
		_current = _next;
		if (_next != end)_next++;
	}
}

XX::Updater::~Updater()
{
}

XX::Updater::Updater():
	_i_updates()
{

}


