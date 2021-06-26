#include "Component.h"
#include "../GameObjects/GameObject.h"
#include "../Events/IUpdate.h"
#include "../Events/IRender.h"

XX::Component::Component() :
	game_object(_game_object),
	active(_active),
	_game_object(nullptr),
	_active(true)
{

}


void XX::Component::Spawn()
{
	_InstallEvents();
	Awake();
	Start();
	if (_active) OnEnable();
}

void XX::Component::Destroy()
{
	OnDestroy();
	_UninstallEvents();
	game_object->RemoveComponent(this);
}

void XX::Component::SetActive(bool active)
{
	if (active && !_active) OnEnable();
	if (!active && _active) OnDisable();

	_active = active;
}



void XX::Component::_SetGameObject(GameObject* game_object)
{
	_game_object = game_object;
}

void XX::Component::_InstallEvents()
{
	IUpdate* iupdate = dynamic_cast<IUpdate*>(this);
	if (iupdate) {
		iupdate->Addto();
	}

	IRender3D* irender3d = dynamic_cast<IRender3D*>(this);
	if (irender3d) {
		irender3d->Addto();
	}

	IRender2D* irender2d = dynamic_cast<IRender2D*>(this);
	if (irender2d) {
		irender2d->Addto();
	}
}

void XX::Component::_UninstallEvents()
{
	IUpdate* iupdate = dynamic_cast<IUpdate*>(this);
	if (iupdate) {
		iupdate->Remove();
	}

	IRender3D* irender3d = dynamic_cast<IRender3D*>(this);
	if (irender3d) {
		irender3d->Remove();
	}

	IRender2D* irender2d = dynamic_cast<IRender2D*>(this);
	if (irender2d) {
		irender2d->Remove();
	}
}


