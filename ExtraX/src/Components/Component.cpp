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

XX::Component::~Component()
{
}

void XX::Component::SetActive(bool& active)
{
	_active = active;
}

void XX::Component::SetActive(bool&& active)
{
	_active = active;
}

void XX::Component::Destroy()
{
	game_object->RemoveComponent(this);
	UninstallEvents();
	delete this;
}

void XX::Component::SetGameObject(GameObject* game_object)
{
	_game_object = game_object;
}

void XX::Component::InstallEvents()
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

void XX::Component::UninstallEvents()
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
