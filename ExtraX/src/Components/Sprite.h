#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"

namespace XX
{
	class Sprite : public Component,public IRender2D
	{
	public:
		virtual ~Sprite();

		void Render2D() override;

	private:
		ID3D11Buffer* _vertex_buffer;

		TexturePtr _texture;

		VertexShaderPtr _vertex_shader;

		PixelShaderPtr _pixel_shader;

		Sprite();

		friend class Component;
	};

	typedef std::shared_ptr<Sprite> SpritePtr;
}

#endif // !_SPRITE_H_

