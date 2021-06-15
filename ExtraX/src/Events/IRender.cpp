#include "IRender.h"
#include "../XX.h"
#include "../Components/Component.h"
#include "../Components/Camera.h"

void XX::IRender::Init()
{
	ExtraX::renderer._i_renders.push_back(this);
}

void XX::IRender::Uninit()
{
	auto i = ExtraX::renderer._i_renders.begin();
	auto end = ExtraX::renderer._i_renders.end();
	for (i; i != end; i++) {
		if (*i == this) {
			ExtraX::renderer._i_renders.erase(i);
			break;
		}
	}
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
	auto i = _i_renders.begin();
	auto end = _i_renders.end();
	for (i; i != end; i++) {
		(*i)->Render();
	}
	i = _i_renders.begin();
	end = _i_renders.end();
	while ( i != end) {
		Component* c = dynamic_cast<Component*>(*i);
		if (c->deleted) {
			_i_renders.erase(i++);
			break;
		}
		else{
			i++;
		}
	}
}

XX::Renderer::~Renderer()
{
}

XX::Renderer::Renderer():
	_i_renders(0)
{
	_i_renders.reserve(1024);
}
