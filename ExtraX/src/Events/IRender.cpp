#include "IRender.h"
#include "../XX.h"
#include "../Components/Component.h"
#include "../Components/Camera.h"



void XX::Renderer3D::Render()
{
	Camera::main_camera->Update();

	_current = _events.begin();
	_next = _current== _events.end()? _events.end():std::next(_current);
	auto end = _events.end();
	while (_current != end)
	{
		(*_current)->Render3D();
		_current = _next;
		if (_next != end)_next++;
	}
}




void XX::Renderer2D::Render()
{
	ExtraX::graphics.SetWorldViewProjection2D();

	_current = _events.begin();
	_next = _current == _events.end() ? _events.end() : std::next(_current);
	auto end = _events.end();
	while (_current != end)
	{
		(*_current)->Render2D();
		_current = _next;
		if (_next != end)_next++;
	}
}



