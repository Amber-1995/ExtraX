#include "../XX.h"
#include "Data.h"

#include "../Helper.h"



XX::Mesh::Mesh(std::vector<XXVertex3D>& vertices, std::vector<UINT>& indices, const std::string& texture_file)
{
	_texture = Texture::Load(texture_file);

	_vertices_num = (UINT)vertices.size();
	D3D11_BUFFER_DESC vbd{};
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(XXVertex3D) * _vertices_num;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA vsd{};
	vsd.pSysMem = vertices.data();
	ExtraX::graphics.device->CreateBuffer(&vbd, &vsd, _vertex_buffer.GetAddressOf());


	_indices_num = (UINT)indices.size();
	D3D11_BUFFER_DESC ibd{};
	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(UINT) * _indices_num;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA isd{};
	isd.pSysMem = indices.data();
	ExtraX::graphics.device->CreateBuffer(&ibd, &isd, _index_buffer.GetAddressOf());

	_material = Graphics::defualt_material;
}

void XX::Mesh::Edit(const XXVertex3D* new_vertices, const UINT* new_indices)
{
	D3D11_MAPPED_SUBRESOURCE vmsr;
	D3D11_MAPPED_SUBRESOURCE imsr;
	ExtraX::graphics.device_context->Map(_vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &vmsr);
	ExtraX::graphics.device_context->Map(_index_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &imsr);

	XXVertex3D* vertex = (XXVertex3D*)vmsr.pData;
	UINT* index = (UINT*)imsr.pData;

	memcpy(vertex, new_vertices, sizeof(XXVertex3D) * _vertices_num);
	memcpy(index, new_indices, sizeof(UINT) * _indices_num);

	ExtraX::graphics.device_context->Unmap(_vertex_buffer.Get(), 0);
	ExtraX::graphics.device_context->Unmap(_index_buffer.Get(), 0);
}

void XX::Mesh::SetTexture(TexturePtr texture)
{
	_texture = texture;
}

void XX::Mesh::SetMaterial(XXMaterial material)
{
	_material = material;
}


void XX::Mesh::Apply()
{
	_texture->Apply();

	ExtraX::graphics.SetMaterial(_material);

	UINT stride = sizeof(XXVertex3D);
	UINT offset = 0;
	ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, _vertex_buffer.GetAddressOf(), &stride, &offset);
	ExtraX::graphics.device_context->IASetIndexBuffer(_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ExtraX::graphics.device_context->DrawIndexed(_indices_num, 0, 0);
}

XX::Meshes::Meshes(std::string file_name)
{
	Assimp::Importer importer;

	_directory = StringHelper::GetDirectoryFromPath(file_name);

	const aiScene* pScene = importer.ReadFile(file_name, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (pScene == nullptr)
	{
		throw std::exception("Meshes load failure!");
	}

	this->ProcessNode(pScene->mRootNode, pScene);
}



void XX::Meshes::Apply()
{
	for (auto& m : _meshes_vector){
		m->Apply();
	}
}

void XX::Meshes::ProcessNode(aiNode* node, const aiScene* scene)
{

	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void XX::Meshes::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{

	std::vector<XXVertex3D> vertices;
	std::vector<UINT> indices;
	
	for (UINT i = 0; i < mesh->mNumVertices; i++){
		XXVertex3D vertex;


		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		
		vertex.diffuse = { 1.0f,1.0f,1.0f,1.0f };


		if (mesh->mTextureCoords[0]){
			vertex.tex_coord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.tex_coord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++){
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	std::string texture_file = DEFAULT_TEXTRUE;
	if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
		aiString f;
		material->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0,&f);
		texture_file =_directory + "\\" +f.C_Str();
	}

	XXMaterial m{};
	aiColor4D color{};
	aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
	m.diffuse = { color.r,color.g,color.b,color.a };
	aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
	m.ambient = { color.r,color.g,color.b,color.a };
	aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
	m.specular = { color.r,color.g,color.b,color.a };
	aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &color);
	m.emission = { color.r,color.g,color.b,color.a };
	

	MeshPtr ret(new Mesh(vertices, indices, texture_file));
	ret->SetMaterial(m);

	_meshes_vector.push_back(ret);
}

