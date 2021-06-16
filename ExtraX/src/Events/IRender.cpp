#include "IRender.h"
#include "../XX.h"
#include "../Components/Component.h"
#include "../Components/Camera.h"

void XX::IRender::Addto()
{
	ExtraX::renderer._i_renders.push_back(this);
}

void XX::IRender::Remove()
{
	if (ExtraX::renderer._next!= ExtraX::renderer._i_renders.end() && 
		this == (*ExtraX::renderer._next)) {
		ExtraX::renderer._next++;
	}
	ExtraX::renderer._i_renders.remove(this);
}

void XX::IRender::Set2DMode()
{
	ExtraX::graphics.SetWorldViewProjection2D();
}

void XX::IRender::SetCameraMode()
{
	XX::Camera::current_camera->Update();
}

void XX::Renderer::Render()
{
	_current = _i_renders.begin();
	_next = std::next(_current);
	auto end = _i_renders.end();
	while (_current != end)
	{
		(*_current)->Render();
		_current = _next;
		if (_next != end)_next++;
	}
}

XX::Renderer::~Renderer()
{

}

XX::Renderer::Renderer():
	_i_renders()
{
	
}
