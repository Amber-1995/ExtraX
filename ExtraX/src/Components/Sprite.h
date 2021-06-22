#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"

namespace XX
{
	class Sprite : public Component
	{
	public:
		const float& width;

		const float& height;

		virtual ~Sprite() = default;

		void Resize(float width, float height);

	protected:
		ID3D11BufferPtr _vertex_buffer;

		ID3D11BufferPtr _index_buffer;

		TexturePtr _texture;

		VertexShaderPtr _vertex_shader;

		PixelShaderPtr _pixel_shader;

		float _width;

		float _height;

		DirectX::XMMATRIX _adj_matrix;

		Sprite(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);

	};

	class Sprite2D : public Sprite, public IRender2D
	{
	public:
		void Render2D() override;

	private:
		Sprite2D(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);

		friend class Component;
	};

	class Sprite3D : public Sprite, public IRender3D
	{
	public:
		void Render3D() override;

	protected:
		Sprite3D(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);

		friend class Component;
	};

}

#endif // !_SPRITE_H_

