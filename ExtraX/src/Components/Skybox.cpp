#include "Skybox.h"
#include "../XX.h"
#include "Camera.h"
#include "../GameObjects/GameObject.h"
#include "Transform.h"

XX::Skybox::Skybox()
{
	std::vector<XXVertex3D> vertex(4);
	std::vector<UINT> index(6);
	index[0] = 0; index[1] = 1; index[2] = 2; index[3] = 2; index[4] = 1; index[5] = 3;
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

		_mesh[0] = MeshPtr(new Mesh(vertex, index));
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

		_mesh[1] = MeshPtr(new Mesh(vertex, index));
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

		_mesh[2] = MeshPtr(new Mesh(vertex, index));
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

		_mesh[3] = MeshPtr(new Mesh(vertex, index));
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

		_mesh[4] = MeshPtr(new Mesh(vertex, index));
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

		_mesh[5] = MeshPtr(new Mesh(vertex, index));
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

	for (auto& m:_mesh){
		m->Apply();
	}


}

void XX::Skybox::SetTexture(const std::string top, const std::string bottom, const std::string left, const std::string right, const std::string front, const std::string back)
{
	_mesh[0]->SetTexture(Texture::Load(top));
	_mesh[1]->SetTexture(Texture::Load(bottom));
	_mesh[2]->SetTexture(Texture::Load(left));
	_mesh[3]->SetTexture(Texture::Load(right));
	_mesh[4]->SetTexture(Texture::Load(front));
	_mesh[5]->SetTexture(Texture::Load(back));
}

