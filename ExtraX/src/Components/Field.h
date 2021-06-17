#pragma once
#ifndef _FIELD_H_
#define _FIELD_H_

#include "Component.h"
#include "../Events/IRender.h"
#include "../Data/ExtraXType.h"

namespace XX
{
	class Field : public Component,public IRender3D
	{
	public:
		Field();
		Field(const Field&) = delete;
		Field& operator=(const Field&) = delete;
		virtual ~Field();

		void Render3D() override;
	private:
		D3DXVECTOR3 _position;
		D3DXVECTOR3 _rotation;
		D3DXVECTOR3 _scale;

		ID3D11Buffer* _vertex_buffer;
		Texture* _texture;
		VertexShader* _vertex_shader;
		PixelShader* _pixel_shader;
	};
}

#endif //!_FIELD_H_
