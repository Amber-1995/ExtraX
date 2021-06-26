#include "Field.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"

XX::Field::Field(int row, int column, const std::string texture_file) :
	_row(row),
	_column(column),
	_vertex_shader(nullptr),
	_pixel_shader(nullptr)
{
	int vertex_num = (_row + 1) * (_column + 1);
	int index_num = (_row * _column * 6);
	std::vector<XXVertex3D> vertex(vertex_num);
	for (int i = 0; i < _column + 1; i++)
	{
		for (int j = 0; j < _row + 1; j++)
		{
			vertex[i * (_row + 1) + j].position  = XXVector3(j-(_row/2.0f),0.0f, -i+(_column/2.0f));
			vertex[i * (_row + 1) + j].normal    = XXVector3(0.0f, 1.0f, 0.0f);
			vertex[i * (_row + 1) + j].diffuse   = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[i * (_row + 1) + j].tex_coord = XXVector2(1.0f * j / _row, 1.0f * i / _column);
		}
	}
	std::vector<UINT>index(index_num);
	for (int i = 0; i < _column; i++)
	{
		for (int j = 0; j < _row; j++)
		{
			index[(i * _row + j) * 6 + 0] = (0 + i) + (i * _row + j);
			index[(i * _row + j) * 6 + 1] = (1 + i) + (i * _row + j);
			index[(i * _row + j) * 6 + 2] = (_row + i) + 1 + (i * _row + j);
			index[(i * _row + j) * 6 + 3] = (_row + 1 + i) + (i * _row + j);
			index[(i * _row + j) * 6 + 4] = (1 + i) + (i * _row + j);
			index[(i * _row + j) * 6 + 5] = (_row + 2 + i) + (i * _row + j);
		}
	}

	_mesh = MeshPtr(new Mesh(vertex, index, texture_file));

	

	_vertex_shader = VertexShader::Load("Assets\\Shaders\\vertexLightingVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\vertexLightingPS.cso");
}

void XX::Field::Render3D()
{
	game_object->transform->SetWorldMatrix();
	_vertex_shader->Apply();
	_pixel_shader->Apply();
	ExtraX::graphics.SetMaterial();
	_mesh->Apply();
}
