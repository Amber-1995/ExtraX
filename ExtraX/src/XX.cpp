#include "XX.h"


namespace XX
{
	Graphics	ExtraX::graphics;
	Updater		ExtraX::updater;
	Renderer3D	ExtraX::renderer3d;
	Renderer2D	ExtraX::renderer2d;

	EventManager<IUpdate>* Event<IUpdate>::_event_manager = &ExtraX::updater;
	EventManager<IRender3D>* Event<IRender3D>::_event_manager = &ExtraX::renderer3d;
	EventManager<IRender2D>* Event<IRender2D>::_event_manager = &ExtraX::renderer2d;

}