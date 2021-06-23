#include "Skybox.h"
#include "../XX.h"
#include "Camera.h"
#include "../GameObjects/GameObject.h"
#include "Transform.h"

XX::Skybox::Skybox()
{
	XXVertex3D vertex[4];
	//top
	{
		vertex[0].position	= XXVector3(0.5f, 0.5f, 0.5f);
		vertex[0].normal	= XXVector3(0.0f, -1.0f, 0.0f);
		vertex[0].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].tex_coord = XXVector2(0.0f, 0.0f);

		vertex[1].position	= XXVector3(-0.5f, 0.5f, 0.5f);
		vertex[1].normal	= XXVector3(0.0f, -1.0f, 0.0f);
		vertex[1].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].tex_coord = XXVector2(1.0f, 0.0f);

		vertex[2].position	= XXVector3(0.5f, 0.5f, -0.5f);
		vertex[2].normal	= XXVector3(0.0f, -1.0f, 0.0f);
		vertex[2].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].tex_coord = XXVector2(0.0f, 1.0f);

		vertex[3].position	= XXVector3(-0.5f, 0.5f, -0.5f);
		vertex[3].normal	= XXVector3(0.0f, -1.0f, 0.0f);
		vertex[3].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].tex_coord = XXVector2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XXVertex3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer[0].GetAddressOf());
	}

	//bottom
	{
		vertex[0].position	= XXVector3(0.5f, -0.5f, -0.5f);
		vertex[0].normal	= XXVector3(0.0f, 1.0f, 0.0f);
		vertex[0].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].tex_coord = XXVector2(0.0f, 0.0f);

		vertex[1].position	= XXVector3(-0.5f, -0.5f, -0.5f);
		vertex[1].normal	= XXVector3(0.0f, 1.0f, 0.0f);
		vertex[1].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].tex_coord = XXVector2(1.0f, 0.0f);

		vertex[2].position	= XXVector3(0.5f, -0.5f, 0.5f);
		vertex[2].normal	= XXVector3(0.0f, 1.0f, 0.0f);
		vertex[2].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].tex_coord = XXVector2(0.0f, 1.0f);

		vertex[3].position	= XXVector3(-0.5f, -0.5f, 0.5f);
		vertex[3].normal	= XXVector3(0.0f, 1.0f, 0.0f);
		vertex[3].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].tex_coord = XXVector2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XXVertex3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer[1].GetAddressOf());
	}

	//left
	{
		vertex[0].position =	XXVector3(-0.5f, 0.5f, -0.5f);
		vertex[0].normal =		XXVector3(1.0f, 0.0f, 0.0f);
		vertex[0].diffuse =		XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].tex_coord =	XXVector2(0.0f, 0.0f);

		vertex[1].position =	XXVector3(-0.5f, 0.5f, 0.5f);
		vertex[1].normal =		XXVector3(1.0f, 0.0f, 0.0f);
		vertex[1].diffuse =		XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].tex_coord =	XXVector2(1.0f, 0.0f);

		vertex[2].position =	XXVector3(-0.5f, -0.5f, -0.5f);
		vertex[2].normal =		XXVector3(1.0f, 0.0f, 0.0f);
		vertex[2].diffuse =		XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].tex_coord =	XXVector2(0.0f, 1.0f);

		vertex[3].position =	XXVector3(-0.5f, -0.5f, 0.5f);
		vertex[3].normal =		XXVector3(1.0f, 0.0f, 0.0f);
		vertex[3].diffuse =		XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].tex_coord =	XXVector2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XXVertex3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer[2].GetAddressOf());
	}

	//right
	{
		vertex[0].position	= XXVector3(0.5f, 0.5f, 0.5f);
		vertex[0].normal	= XXVector3(-1.0f, 0.0f, 0.0f);
		vertex[0].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].tex_coord = XXVector2(0.0f, 0.0f);

		vertex[1].position	= XXVector3(0.5f, 0.5f, -0.5f);
		vertex[1].normal	= XXVector3(-1.0f, 0.0f, 0.0f);
		vertex[1].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].tex_coord = XXVector2(1.0f, 0.0f);

		vertex[2].position	= XXVector3(0.5f, -0.5f, 0.5f);
		vertex[2].normal	= XXVector3(-1.0f, 0.0f, 0.0f);
		vertex[2].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].tex_coord = XXVector2(0.0f, 1.0f);

		vertex[3].position	= XXVector3(0.5f, -0.5f, -0.5f);
		vertex[3].normal	= XXVector3(-1.0f, 0.0f, 0.0f);
		vertex[3].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].tex_coord = XXVector2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XXVertex3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer[3].GetAddressOf());
	}

	//front
	{
		vertex[0].position	= XXVector3(0.5f, 0.5f, -0.5f);
		vertex[0].normal	= XXVector3(0.0f, 0.0f, 1.0f);
		vertex[0].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].tex_coord = XXVector2(0.0f, 0.0f);

		vertex[1].position	= XXVector3(-0.5f, 0.5f, -0.5f);
		vertex[1].normal	= XXVector3(0.0f, 0.0f, 1.0f);
		vertex[1].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].tex_coord = XXVector2(1.0f, 0.0f);

		vertex[2].position	= XXVector3(0.5f, -0.5f, -0.5f);
		vertex[2].normal	= XXVector3(0.0f, 0.0f, 1.0f);
		vertex[2].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].tex_coord = XXVector2(0.0f, 1.0f);

		vertex[3].position	= XXVector3(-0.5f, -0.5f, -0.5f);
		vertex[3].normal	= XXVector3(0.0f, 0.0f, 1.0f);
		vertex[3].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].tex_coord = XXVector2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XXVertex3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer[4].GetAddressOf());
	}

	//back
	{
		vertex[0].position	= XXVector3(-0.5f, 0.5f, 0.5f);
		vertex[0].normal	= XXVector3(0.0f, 0.0f, -1.0f);
		vertex[0].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].tex_coord = XXVector2(0.0f, 0.0f);

		vertex[1].position	= XXVector3(0.5f, 0.5f, 0.5f);
		vertex[1].normal	= XXVector3(0.0f, 0.0f, -1.0f);
		vertex[1].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].tex_coord = XXVector2(1.0f, 0.0f);

		vertex[2].position	= XXVector3(-0.5f, -0.5f, 0.5f);
		vertex[2].normal	= XXVector3(0.0f, 0.0f, -1.0f);
		vertex[2].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].tex_coord = XXVector2(0.0f, 1.0f);

		vertex[3].position	= XXVector3(0.5f, -0.5f, 0.5f);
		vertex[3].normal	= XXVector3(0.0f, 0.0f, -1.0f);
		vertex[3].diffuse	= XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].tex_coord = XXVector2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XXVertex3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer[5].GetAddressOf());
	}

	_vertex_shader = VertexShader::Load("Assets\\Shaders\\unlitTextureVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\unlitTexturePS.cso");

	_adj_matrix = DirectX::XMMatrixScaling(5000.0f, 5000.0f, 5000.0f);
}

void XX::Skybox::Render3D()
{
	DirectX::XMMATRIX matrix = Camera::main_camera->game_object->transform->GetMatrix(TRANSFORM_TRANSLATION_MATRIX);
	ExtraX::graphics.SetWorldMatrix(_adj_matrix * matrix);

	_vertex_shader->Apply();
	_pixel_shader->Apply();

	for (int i = 0; i < 6; i++){

		_texture[i]->Apply();

		UINT stride = sizeof(XXVertex3D);
		UINT offset = 0;
		ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, _vertex_buffer[i].GetAddressOf(), &stride, &offset);
		ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		ExtraX::graphics.device_context->Draw(4, 0);
	}


}

void XX::Skybox::SetTexture(const std::string top, const std::string bottom, const std::string left, const std::string right, const std::string front, const std::string back)
{
	_texture[0] = Texture::Load(top);
	_texture[1] = Texture::Load(bottom);
	_texture[2] = Texture::Load(left);
	_texture[3] = Texture::Load(right);
	_texture[4] = Texture::Load(front);
	_texture[5] = Texture::Load(back);
}

