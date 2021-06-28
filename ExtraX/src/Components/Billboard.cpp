#include "Billboard.h"

#include "Camera.h"
#include "../XX.h"
#include "Transform.h"
#include "../GameObjects/GameObject.h"

using namespace DirectX;

void XX::Billboard::Render3D()
{
	XMMATRIX t_matrix = game_object->transform->GetMatrix(TRANSFORM_TRANSLATION_MATRIX);
	XMMATRIX r_matrix = Camera::main_camera->game_object->transform->GetMatrix(TRANSFORM_ROTATION_MATRIX);
	XMMATRIX s_matrix = game_object->transform->GetMatrix(TRANSFORM_SCALING_MATRIX);
	ExtraX::graphics.SetWorldMatrix(_adj_matrix * s_matrix * r_matrix * t_matrix);


	_vertex_shader->Apply();
	_pixel_shader->Apply();
	ExtraX::graphics.SetMaterial();
	_mesh->Apply();
}

XX::Billboard::Billboard(float width, float height, const std::string& texture_file):
	Sprite3D(width,height,texture_file)
{
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\unlitTextureVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\unlitTexturePS.cso");
}
