#include "Field.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"

XX::Field::Field() :
	_vertex_buffer(nullptr),
	_texture(nullptr),
	_vertex_shader(nullptr),
	_pixel_shader(nullptr)
{
	VERTEX_3D vertex[4];

	vertex[0].position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	vertex[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].tex_coord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	vertex[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].tex_coord = D3DXVECTOR2(5.0f, 0.0f);

	vertex[2].position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	vertex[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].tex_coord = D3DXVECTOR2(0.0f, 5.0f);

	vertex[3].position = D3DXVECTOR3(10.0f, 00.0f, -10.0f);
	vertex[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].tex_coord = D3DXVECTOR2(5.0f, 5.0f);

	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA sd{};

	sd.pSysMem = vertex;

	ExtraX::graphics.device->CreateBuffer(&bd, &sd, &_vertex_buffer);

	_texture = Texture::Load("Assets\\Textures\\ground.png");
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\vertexLightingVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\vertexLightingPS.cso");
}

XX::Field::~Field()
{
}

void XX::Field::Render3D()
{

	
	game_object->transform->SetMatrix();
	_vertex_shader->Apply();
	_pixel_shader->Apply();
	_texture->Apply();

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, &_vertex_buffer, &stride, &offset);

	MATERIAL material;
	ZeroMemory(&material, sizeof(MATERIAL));
	material.diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ExtraX::graphics.SetMaterial(material);
	ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	ExtraX::graphics.device_context->Draw(4, 0);
}
