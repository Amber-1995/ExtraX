#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "Resource.h"
#include "Texture.h"
#include "ExtraXType.h"

namespace XX
{
	// マテリアル構造体
	struct XXModelMaterial
	{
		char		name[1024];
		XXMaterial	material;
		char		texture_name[1024];
		TexturePtr	texture;
	};


	// 描画サブセット構造体
	struct XXSubset
	{
		unsigned int	start_index;
		unsigned int	index_num;
		XXModelMaterial	material;
	};


	// モデル構造体
	struct XXModel
	{
		XXVertex3D*		vertex_array;
		unsigned int	vertex_num;

		unsigned int*	index_array;
		unsigned int	index_num;

		XXSubset*		subset_array;
		unsigned int	subset_num;
	};


	class Model : public Resource<Model>
	{
	public:
		void Apply() override;

		virtual ~Model();

	private:
		ID3D11BufferPtr _vertex_buffer;

		ID3D11BufferPtr _index_buffer;

		XXSubset* _subset_array;

		unsigned int _subset_num;

		Model(std::string file_name);

		Model(const Model&) = delete;

		Model& operator=(const Model&) = delete;

		void _LoadObj(const char* file_name, XXModel* model);

		void _LoadMaterial(const char* file_name, XXModelMaterial** material_array, unsigned int* material_num);

		friend class Resource<Model>;
	};

	typedef std::shared_ptr<Model> ModelPtr;
	std::unordered_map<std::string, ModelPtr> Model::_resources;
}

#endif //!_MODEL_H_