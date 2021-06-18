#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "Component.h"
#include "../Events/IRender.h"
#include <string>

namespace XX
{
	// マテリアル構造体
	struct MODEL_MATERIAL
	{
		char						Name[256];
		MATERIAL					Material;
		char						TextureName[256];
		ID3D11ShaderResourceView* Texture;

	};


	// 描画サブセット構造体
	struct SUBSET
	{
		unsigned int	StartIndex;
		unsigned int	IndexNum;
		MODEL_MATERIAL	Material;
	};


	// モデル構造体
	struct MODEL
	{
		VERTEX_3D* VertexArray;
		unsigned int	VertexNum;

		unsigned int* IndexArray;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
		unsigned int	IndexNum;

		SUBSET* SubsetArray;
		unsigned int	SubsetNum;
	};

	class Mesh : public Component,public IRender3D
	{
	public:
		Mesh(std::string file_name);

		Mesh(const Mesh&) = delete;

		Mesh& operator=(const Mesh&) = delete;

		virtual ~Mesh();

		void Render3D() override;

	private:
		ID3D11Buffer* m_VertexBuffer;

		ID3D11Buffer* m_IndexBuffer;

		SUBSET* m_SubsetArray;

		unsigned int	m_SubsetNum;

		void LoadObj(const char* FileName, MODEL* Model);

		void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);

	};
}






#endif // !_MODEL_H_

