#include "Field.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"

XX::Field::Field(int row, int column, const std::string texture_file) :
	_row(row),
	_column(column),
	_vertex_buffer(nullptr),
	_index_buffer(nullptr),
	_texture(nullptr),
	_vertex_shader(nullptr),
	_pixel_shader(nullptr)
{
	int vertex_num = (_row + 1) * (_column + 1);
	int index_num = (_row) * (_column * 2 + 4);
	{
		XXVertex3D* vertex = new XXVertex3D[vertex_num];
		for (int i = 0; i < _column + 1; i++)
		{
			for (int j = 0; j < _row + 1; j++)
			{
				vertex[i * (_row + 1) + j].position = XXVector3(j - (_row / 2.0f), 0.0f, -i + (_column / 2.0f));
				vertex[i * (_row + 1) + j].normal = XXVector3(0.0f, 1.0f, 0.0f);
				vertex[i * (_row + 1) + j].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[i * (_row + 1) + j].tex_coord = XXVector2(1.0f * j / _row, 1.0f * i / _column);
			}
		}

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(XXVertex3D) * vertex_num;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer.GetAddressOf());

		delete[] vertex;
	}

	{
		UINT* index = new UINT[index_num];
		for (int i = 0; i < _row; i++)
		{
			index[i * (_column * 2 + 4)] = i;
			for (int j = 0; j < _column + 1; j++)
			{
				index[i * (_column * 2 + 4) + 1 + j * 2] = i + 1 + (_row + 1) * j;
				index[i * (_column * 2 + 4) + 2 + j * 2] = i + (_row + 1) * j;
			}
			index[(i + 1) * (_column * 2 + 4) - 1] = vertex_num - _row + i;
		}

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(UINT) * index_num;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = index;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _index_buffer.GetAddressOf());

		delete[]index;
	}


	_texture = Texture::Load(texture_file.c_str());
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\vertexLightingVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\vertexLightingPS.cso");
}

XX::Field::~Field()
{
}

void XX::Field::Render3D()
{
	

	game_object->transform->SetWorldMatrix();
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
	int index_num = (_row) * (_column * 2 + 4);
	ExtraX::graphics.device_context->DrawIndexed(index_num, 0, 0);
	
}
