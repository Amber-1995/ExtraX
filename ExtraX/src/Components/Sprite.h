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

		void Resize(float width, float height);

		void SetTexture(TexturePtr texture);

		void SetVertex(const XXVertex3D* vertex_data);

	protected:
		ID3D11BufferPtr _vertex_buffer;

		TexturePtr _texture;

		VertexShaderPtr _vertex_shader;

		PixelShaderPtr _pixel_shader;

		float _width;

		float _height;

		DirectX::XMMATRIX _adj_matrix;

		Sprite(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

	};
	typedef std::shared_ptr<Sprite> SpritePtr;

	class Sprite2D : public Sprite, public IRender2D
	{
	public:
		virtual ~Sprite2D() = default;

		void Render2D() override;

	private:
		Sprite2D(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Sprite2D(const Sprite2D&) = delete;
		Sprite2D& operator=(const Sprite2D&) = delete;

		friend class Component;
	};
	typedef std::shared_ptr<Sprite2D> Sprite2DPtr;

	class Sprite3D : public Sprite, public IRender3D
	{
	public:
		virtual ~Sprite3D() = default;

		void Render3D() override;

	protected:
		Sprite3D(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Sprite3D(const Sprite3D&) = delete;
		Sprite3D& operator=(const Sprite3D&) = delete;

		friend class Component;
	};
	typedef std::shared_ptr<Sprite3D> Sprite3DPtr;

}

#endif // !_SPRITE_H_

