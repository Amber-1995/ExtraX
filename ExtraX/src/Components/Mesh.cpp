#include "Mesh.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"


#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

using namespace DirectX;

XX::Mesh::Mesh(std::string file_name) :
	_adj_matrix(XMMatrixIdentity())
{
	_model = Model::Load(file_name);
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\vertexLightingVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\vertexLightingPS.cso");
}



void XX::Mesh::Render3D()
{

	game_object->transform->SetWorldMatrix(_adj_matrix);
	_vertex_shader->Apply();
	_pixel_shader->Apply();

	_model->Apply();
	
}

void XX::Mesh::AdjustTransform(XXVector3 pos_offset, XXVector3 rot_offset, XXVector3 scl_oofset)
{
	XMMATRIX t = XMMatrixTranslation(pos_offset.x, pos_offset.y, pos_offset.z);
	XMMATRIX r = XMMatrixRotationRollPitchYaw(rot_offset.x, rot_offset.y, rot_offset.z);
	XMMATRIX s = XMMatrixScaling(scl_oofset.x, scl_oofset.y, scl_oofset.z);
	_adj_matrix = s * r * t;
}

