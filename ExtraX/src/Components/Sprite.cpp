#include "Sprite.h"
#include "../XX.h"
#include "Transform.h"
#include "../GameObjects/GameObject.h"

XX::Sprite::Sprite(float width, float height, const std::string& texture_file) :
	width(_width),
	height(_height),
	_vertex_buffer(nullptr),
	_texture(nullptr),
	_vertex_shader(nullptr),
	_pixel_shader(nullptr),
	_width(width),
	_height(height)
{
	{
		XXVertex3D vertex[4];

		vertex[0].position = XXVector3(-1.0f/2.0f, -1.0f /2.0f, 0.0f);
		vertex[0].normal = XXVector3(0.0f, 0.0f, 0.0f);
		vertex[0].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].tex_coord = XXVector2(0.0f, 0.0f);

		vertex[1].position = XXVector3(1.0f /2.0f, -1.0f / 2.0f, 0.0f);
		vertex[1].normal = XXVector3(0.0f, 0.0f, 0.0f);
		vertex[1].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].tex_coord = XXVector2(1.0f, 0.0f);

		vertex[2].position = XXVector3(-1.0f / 2.0f, 1.0f/ 2.0f, 0.0f);
		vertex[2].normal = XXVector3(0.0f, 0.0f, 0.0f);
		vertex[2].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].tex_coord = XXVector2(0.0f, 1.0f);

		vertex[3].position = XXVector3(1.0f / 2.0f, 1.0f / 2.0f, 0.0f);
		vertex[3].normal = XXVector3(0.0f, 0.0f, 0.0f);
		vertex[3].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].tex_coord = XXVector2(1.0f, 1.0f);


		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XXVertex3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags =D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer.GetAddressOf());
	}

	{
		UINT index[4] = { 0,1,2,3 };

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(UINT) * 4;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = index;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _index_buffer.GetAddressOf());
	}

	_texture = Texture::Load(texture_file.c_str());
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\unlitTextureVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\unlitTexturePS.cso");

	_adj_matrix = DirectX::XMMatrixScaling(_width, _height, 1.0f);
	
}

void XX::Sprite::Resize(float width, float height)
{
	_width = width;
	_height = height;
	_adj_matrix = DirectX::XMMatrixScaling(_width, _height, 1.0f);
}

void XX::Sprite2D::Render2D()
{
	game_object->transform->SetWorldMatrix(_adj_matrix);
	_vertex_shader->Apply();
	_pixel_shader->Apply();
	_texture->Apply();


	UINT stride = sizeof(XXVertex3D);
	UINT offset = 0;
	ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, _vertex_buffer.GetAddressOf(), &stride, &offset);

	ExtraX::graphics.device_context->IASetIndexBuffer(_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	ExtraX::graphics.device_context->DrawIndexed(4, 0, 0);
}

XX::Sprite2D::Sprite2D(float width, float height, const std::string& texture_file):
	Sprite(width,height,texture_file)
{

}

void XX::Sprite3D::Render3D()
{
	game_object->transform->SetWorldMatrix(_adj_matrix);
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

XX::Sprite3D::Sprite3D(float width, float height, const std::string& texture_file):
	Sprite(width, height, texture_file)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	ExtraX::graphics.device_context->Map(_vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	XXVertex3D* vertex = (XXVertex3D*)msr.pData;

	vertex[0].position = XXVector3(-1.0f / 2.0f, 1.0f / 2.0f, 0.0f);
	vertex[0].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[0].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].tex_coord = XXVector2(0.0f, 0.0f);

	vertex[1].position = XXVector3(1.0f / 2.0f, 1.0f / 2.0f, 0.0f);
	vertex[1].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[1].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].tex_coord = XXVector2(1.0f, 0.0f);

	vertex[2].position = XXVector3(-1.0f / 2.0f, -1.0f / 2.0f, 0.0f);
	vertex[2].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[2].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].tex_coord = XXVector2(0.0f, 1.0f);

	vertex[3].position = XXVector3(1.0f / 2.0f, -1.0f / 2.0f, 0.0f);
	vertex[3].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[3].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].tex_coord = XXVector2(1.0f, 1.0f);

	ExtraX::graphics.device_context->Unmap(_vertex_buffer.Get(),0);
}
