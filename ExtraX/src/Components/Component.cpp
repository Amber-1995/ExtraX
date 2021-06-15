#include "Component.h"
#include "../Events/IUpdate.h"
#include "../Events/IRender.h"

XX::Component::Component() :
	game_object(_game_object),
	active(_active),
	deleted(_deleted),
	_game_object(nullptr),
	_active(true),
	_deleted(false)
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

void XX::Component::Delete()
{
	_deleted = true;
}

void XX::Component::SetGameObject(GameObject* game_object)
{
	_game_object = game_object;
}

void XX::Component::InitEvents()
{
	IUpdate* iupdate = dynamic_cast<IUpdate*>(this);
	if (iupdate) {
		iupdate->Init();
	}

	IRender* irender = dynamic_cast<IRender*>(this);
	if (irender) {
		irender->Init();
	}
}
