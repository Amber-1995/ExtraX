#include "IRender.h"
#include "../XX.h"
#include "../Components/Component.h"
#include "../Components/Camera.h"



void XX::Renderer3D::Render()
{
	Camera::main_camera->Update();

	for (int i = 0; i < _events.width; i++){
		for (int j = 0; j < _events.length; j++){
			if (_events.GetUnit(i, j).is_using)
			{
				_events.GetUnit(i, j).data->Render3D();
			}
		}
	}
}




void XX::Renderer2D::Render()
{
	ExtraX::graphics.SetWorldViewProjection2D();

	for (int i = 0; i < _events.width; i++) {
		for (int j = 0; j < _events.length; j++) {
			if (_events.GetUnit(i, j).is_using)
			{
				_events.GetUnit(i, j).data->Render2D();
			}
		}
	}
}



