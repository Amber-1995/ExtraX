#include "Sprite.h"
#include "../XX.h"
#include "Transform.h"
#include "../GameObjects/GameObject.h"

XX::Sprite::Sprite(float width, float height, const std::string& texture_file) :
	width(_width),
	height(_height),
	_vertex_shader(nullptr),
	_pixel_shader(nullptr),
	_width(width),
	_height(height),
	_adj_matrix(DirectX::XMMatrixIdentity())
{
	std::vector<XXVertex3D> vertex(4);
	vertex[0].position = XXVector3(-0.5f, 0.5f, 0.0f);
	vertex[0].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[0].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].tex_coord = XXVector2(0.0f, 0.0f);
	vertex[1].position = XXVector3(0.5f, 0.5f, 0.0f);
	vertex[1].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[1].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].tex_coord = XXVector2(1.0f, 0.0f);
	vertex[2].position = XXVector3(-0.5f, -0.5f, 0.0f);
	vertex[2].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[2].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].tex_coord = XXVector2(0.0f, 1.0f);
	vertex[3].position = XXVector3(0.5f, -0.5f, 0.0f);
	vertex[3].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[3].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].tex_coord = XXVector2(1.0f, 1.0f);
		
	std::vector<UINT> indices(6);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;
		
	_mesh = MeshPtr(new Mesh(vertex, indices, texture_file));

	
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\unlitTextureVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\unlitTexturePS.cso");
	_adj_matrix = DirectX::XMMatrixScaling(_width, _height, 1.0f);
	
}



void XX::Sprite::SetTexture(TexturePtr texture)
{
	_mesh->SetTexture(texture);
}

void XX::Sprite::SetVertex(const XXVertex3D* vertex_data)
{
	std::vector<UINT> index_data(6);
	index_data[0] = 0;
	index_data[1] = 1;
	index_data[2] = 2;
	index_data[3] = 2;
	index_data[4] = 1;
	index_data[5] = 3;

	_mesh->Edit(vertex_data, index_data.data());
}

void XX::Sprite2D::Render2D()
{
	game_object->transform->SetWorldMatrix(_adj_matrix);
	_vertex_shader->Apply();
	_pixel_shader->Apply();
	_mesh->Apply();
}

XX::Sprite2D::Sprite2D(float width, float height, const std::string& texture_file):
	Sprite(width,height,texture_file)
{
	_adj_matrix *= DirectX::XMMatrixRotationX(DirectX::XM_PI);
}

void XX::Sprite3D::Render3D()
{
	game_object->transform->SetWorldMatrix(_adj_matrix);
	_vertex_shader->Apply();
	_pixel_shader->Apply();
	_mesh->Apply();
}

XX::Sprite3D::Sprite3D(float width, float height, const std::string& texture_file):
	Sprite(width, height, texture_file)
{
	_vertex_shader = VertexShader::Load("Assets\\Shaders\\vertexLightingVS.cso");
	_pixel_shader = PixelShader::Load("Assets\\Shaders\\vertexLightingPS.cso");
}
