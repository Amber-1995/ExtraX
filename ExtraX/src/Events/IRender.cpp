#include "IRender.h"
#include "../XX.h"
#include "../Components/Component.h"
#include "../Components/Camera.h"


void XX::IRender2D::Addto()
{
	ExtraX::renderer2d._i_render2ds.push_front(this);

}

void XX::IRender2D::Remove()
{
	if (ExtraX::renderer2d._next != ExtraX::renderer2d._i_render2ds.end() &&
		this == (*ExtraX::renderer2d._next)) {
		ExtraX::renderer2d._next++;
	}
	ExtraX::renderer2d._i_render2ds.remove(this);
}

void XX::IRender3D::Addto()
{
	ExtraX::renderer3d._i_render3ds.push_front(this);
}

void XX::IRender3D::Remove()
{
	if (ExtraX::renderer3d._next!= ExtraX::renderer3d._i_render3ds.end() && 
		this == (*ExtraX::renderer3d._next)) {
		ExtraX::renderer3d._next++;
	}
	ExtraX::renderer3d._i_render3ds.remove(this);
}


void XX::Renderer3D::Render()
{
	Camera::main_camera->Update();

	_current = _i_render3ds.begin();
	_next = std::next(_current);
	auto end = _i_render3ds.end();
	while (_current != end)
	{
		(*_current)->Render3D();
		_current = _next;
		if (_next != end)_next++;
	}
}



XX::Renderer3D::Renderer3D():
	_i_render3ds()
{
	
}

XX::Renderer3D::~Renderer3D()
{

}



void XX::Renderer2D::Render()
{
	ExtraX::graphics.SetWorldViewProjection2D();

	_current = _i_render2ds.begin();
	_next = std::next(_current);
	auto end = _i_render2ds.end();
	while (_current != end)
	{
		(*_current)->Render2D();
		_current = _next;
		if (_next != end)_next++;
	}
}



XX::Renderer2D::Renderer2D():
	_i_render2ds()
{

}

XX::Renderer2D::~Renderer2D()
{

}
