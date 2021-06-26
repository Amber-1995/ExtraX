#pragma once
#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"

namespace XX
{
	class Skybox : public Component , public IRender3D
	{
	/*====================コンストラクターとデストラクター====================*/
	public:
		virtual ~Skybox() = default;
	private:
		Skybox();
		Skybox(const Skybox&) = delete;
		Skybox& operator=(Skybox&) = delete;
	/*================================メンバー================================*/
	private:
		VertexShaderPtr _vertex_shader;
		PixelShaderPtr _pixel_shader;
		MeshPtr _mesh[6];
		DirectX::XMMATRIX _adj_matrix;

	/*================================メソッド================================*/
	public:
		void Render3D() override;
		void SetTexture(
			const std::string top,
			const std::string bottom,
			const std::string left,
			const std::string right,
			const std::string front,
			const std::string back
		);

	/*================================フレンド================================*/
		friend class Component;
	};
}

#endif // !_SKYBOX_H_
