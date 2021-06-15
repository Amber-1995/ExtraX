#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Component.h"
#include "../Events/IRender.h"

namespace XX
{
	class Sprite : public Component,public IRender
	{
	public:
		Sprite();

		virtual ~Sprite();

		void Render() override;
	private:

		ID3D11Buffer* _vertex_buffer;

		ID3D11ShaderResourceView* _texture;

		ID3D11VertexShader* _vertex_shader;

		ID3D11PixelShader* _pixel_shader;

		ID3D11InputLayout* _vertex_layout;
	};
}

#endif // !_SPRITE_H_

