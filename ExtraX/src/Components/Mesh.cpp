#include "Mesh.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"


#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

XX::Mesh::Mesh(std::string file_name)
{
	_model = Model::Load(file_name);
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\vertexLightingVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\vertexLightingPS.cso");
}


void XX::Mesh::Render3D()
{

	game_object->transform->SetWorldMatrix();
	_vertex_shader->Apply();
	_pixel_shader->Apply();

	_model->Apply();
	
}

