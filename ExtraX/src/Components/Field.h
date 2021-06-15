#pragma once
#ifndef _FIELD_H_
#define _FIELD_H_

#include "Component.h"
#include "../Events/IRender.h"

namespace XX
{
	class Field : public Component,public IRender
	{
	public:
		Field();
		Field(const Field&) = delete;
		Field& operator=(const Field&) = delete;
		virtual ~Field();

		void Render() override;
	private:
		D3DXVECTOR3 _position;
		D3DXVECTOR3 _rotation;
		D3DXVECTOR3 _scale;

		ID3D11Buffer* _vertex_buffer;
		ID3D11ShaderResourceView* _texture;

		ID3D11VertexShader* _vertex_shader;
		ID3D11PixelShader* _pixel_shader;
		ID3D11InputLayout* _vertex_layout;
	};
}

#endif //!_FIELD_H_
