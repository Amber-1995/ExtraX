#pragma once
#ifndef _FIELD_H_
#define _FIELD_H_

#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"

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

		ID3D11Buffer* _vertex_buffer;
		TexturePtr _texture;
		VertexShaderPtr _vertex_shader;
		PixelShaderPtr _pixel_shader;
	};
}

#endif //!_FIELD_H_
