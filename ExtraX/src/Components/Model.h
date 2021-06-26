#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"
#include <string>

namespace XX
{
	
	class Model : public Component, public IRender3D
	{
		/*====================コンストラクターとデストラクター====================*/
	public:
		virtual ~Model() = default;
	private:
		Model(std::string file_name);
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		/*================================メンバー================================*/
	private:
		VertexShaderPtr _vertex_shader;
		PixelShaderPtr _pixel_shader;
		MeshesPtr _model;
		DirectX::XMMATRIX _adj_matrix;

		/*================================メソッド================================*/
	public:
		void Render3D() override;
		void AdjustTransform(XXVector3 pos_offset, XXVector3 rot_offset, XXVector3 scl_oofset);

		/*================================フレンド================================*/
		friend class Component;
	};
	typedef std::shared_ptr<Model> ModelPtr;
}






#endif // !_MODEL_H_

