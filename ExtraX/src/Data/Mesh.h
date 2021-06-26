#pragma once
#ifndef _MESH_H_
#define _MESH_H_
#include "Resource.h"
#include "Texture.h"
#include "ExtraXType.h"

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace XX
{
	class Mesh
	{
	/*====================コンストラクターとデストラクター====================*/
	public:
		Mesh(std::vector<XXVertex3D>& vertices, std::vector<UINT>& indices,const std::string& texture_file = DEFAULT_TEXTRUE);
		virtual ~Mesh() = default;
	
	/*================================メンバー================================*/
	private:
		UINT _vertices_num;
		ID3D11BufferPtr _vertex_buffer;
		UINT _indices_num;
		ID3D11BufferPtr _index_buffer;
		TexturePtr _texture;
		
	/*================================メソッド================================*/
	public:
		void Edit(const XXVertex3D* new_vertices, const UINT* new_indices);
		void SetTexture(TexturePtr texture);
		void Apply();
	};
	typedef std::shared_ptr<Mesh> MeshPtr;



	class Meshes : public Resource<Meshes>
	{
	/*====================コンストラクターとデストラクター====================*/
	public:
		Meshes() = default;
		virtual ~Meshes() = default;
	private:
		Meshes(std::string file_name);
		Meshes(const Meshes&) = delete;
		Meshes& operator=(const Meshes&) = delete;
	
	/*================================メンバー================================*/
	private:
		std::vector<MeshPtr> _meshes_vector;
		std::string _directory;
	/*================================メソッド================================*/
	
	public:
		void Apply() override;
	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	/*================================フレンド================================*/
		friend class Resource<Meshes>;
	};
	typedef std::shared_ptr<Meshes> MeshesPtr;


	
}

#endif //!_MESH_H_