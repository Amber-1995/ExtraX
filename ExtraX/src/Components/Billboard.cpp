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

	//r_matrix = XMMatrixInverse(nullptr, r_matrix);

	ExtraX::graphics.SetWorldMatrix(_adj_matrix * s_matrix * r_matrix * t_matrix);
	_vertex_shader->Apply();
	_pixel_shader->Apply();
	_texture->Apply();


	UINT stride = sizeof(XXVertex3D);
	UINT offset = 0;
	ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, _vertex_buffer.GetAddressOf(), &stride, &offset);

	ExtraX::graphics.device_context->IASetIndexBuffer(_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	XXMaterial material;
	ZeroMemory(&material, sizeof(XXMaterial));
	material.diffuse = XXColor(1.0f, 1.0f, 1.0f, 1.0f);
	ExtraX::graphics.SetMaterial(material);
	ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	ExtraX::graphics.device_context->DrawIndexed(4, 0, 0);

}

XX::Billboard::Billboard(float width, float height, const std::string& texture_file):
	Sprite3D(width,height,texture_file)
{
}
