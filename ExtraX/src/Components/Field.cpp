#include "Field.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"

XX::Field::Field() :
	_position(0, 0, 0),
	_rotation(0, 0, 0),
	_scale(1, 1, 1),
	_vertex_buffer(nullptr),
	_texture(nullptr),
	_vertex_shader(nullptr),
	_pixel_shader(nullptr),
	_vertex_layout(nullptr)
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

	D3DX11CreateShaderResourceViewFromFile(
		ExtraX::graphics.device,
		"Assets\\Textures\\ground.png",
		nullptr,
		nullptr,
		&_texture,
		nullptr
	);

	assert(_texture);

	ExtraX::graphics.CreateVertexShader(&_vertex_shader, &_vertex_layout, "Assets\\Shaders\\vertexLightingVS.cso");
	ExtraX::graphics.CreatePixelShader(&_pixel_shader, "Assets\\Shaders\\vertexLightingPS.cso");
}

XX::Field::~Field()
{
}

void XX::Field::Render()
{
	SetCameraMode();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, game_object->transform->scale.x, game_object->transform->scale.y, game_object->transform->scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, game_object->transform->rotation.x, game_object->transform->rotation.y, game_object->transform->rotation.z);
	D3DXMatrixTranslation(&trans, game_object->transform->position.x, game_object->transform->position.y, game_object->transform->position.z);
	world = scale * rot * trans;
	ExtraX::graphics.SetWorldMatrix(&world);

	ExtraX::graphics.device_context->IASetInputLayout(_vertex_layout);

	ExtraX::graphics.device_context->VSSetShader(_vertex_shader, nullptr, 0);
	ExtraX::graphics.device_context->PSSetShader(_pixel_shader, nullptr, 0);


	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, &_vertex_buffer, &stride, &offset);

	MATERIAL material;
	ZeroMemory(&material, sizeof(MATERIAL));
	material.diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ExtraX::graphics.SetMaterial(material);


	ExtraX::graphics.device_context->PSSetShaderResources(0, 1, &_texture);
	ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	ExtraX::graphics.device_context->Draw(4, 0);
}