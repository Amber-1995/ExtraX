#include "Game/Components/Polygon.h"
#include "Common/Math.h"



namespace XX::Game::Components
{
	using namespace Math;

	void Rect2D::Render2D(size_t thread)
	{
		_transform->Set(thread);
		_shader->Set(thread);
		_mesh->Set(thread);
	}
	void Rect2D::OnStart()
	{
		_transform = GetComponent<Transform>();
	}
	Rect2D::Rect2D()
	{
		std::vector<Vertex> vertices(4);
		vertices[0].position  = Float3(-500.0f, -500.f, 0.0f);
		vertices[0].normal    = Float3(0.0f, 0.0f, -1.0f);
		vertices[0].diffuse   = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[0].tex_coord = Float2(0.0f, 0.0f);
		vertices[1].position  = Float3(500.0f, -500.0f, 0.0f);
		vertices[1].normal    = Float3(0.0f, 0.0f, -1.0f);
		vertices[1].diffuse   = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[1].tex_coord = Float2(1.0f, 0.0f);
		vertices[2].position  = Float3(-500.0f, 500.0f, 0.0f);
		vertices[2].normal    = Float3(0.0f, 0.0f, -1.0f);
		vertices[2].diffuse   = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[2].tex_coord = Float2(0.0f, 1.0f);
		vertices[3].position  = Float3(500.f, 500.0f, 0.0f);
		vertices[3].normal    = Float3(0.0f, 0.0f, -1.0f);
		vertices[3].diffuse   = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[3].tex_coord = Float2(1.0f, 1.0f);

		std::vector<Index> indices(6);
		indices[0] = 0;
		indices[1] = 2;
		indices[2] = 1;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 1;

		_mesh = ExtraX::graphics->CreateMesh(vertices, indices);

		_shader = ExtraX::asset_importer->ImportShader("Assets\\Shader\\2D.XXShader");
	}
}


