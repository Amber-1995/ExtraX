#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Component.h"
#include "../Events/IRender.h"
#include "../Data/ExtraXType.h"

namespace XX
{
	class Sprite : public Component,public IRender2D
	{
	public:
		Sprite();

		virtual ~Sprite();

		void Render2D() override;
	private:

		ID3D11Buffer* _vertex_buffer;

		Texture* _texture;

		VertexShader* _vertex_shader;

		PixelShader* _pixel_shader;

	};
}

#endif // !_SPRITE_H_

