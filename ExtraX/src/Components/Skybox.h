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

	private:
		ID3D11BufferPtr _vertex_buffer[6];

		TexturePtr _texture[6];

		VertexShaderPtr _vertex_shader;

		PixelShaderPtr _pixel_shader;

		DirectX::XMMATRIX _adj_matrix;

		Skybox();
		Skybox(const Skybox&) = delete;
		Skybox& operator=(Skybox&) = delete;

		friend class Component;
	};
}

#endif // !_SKYBOX_H_
