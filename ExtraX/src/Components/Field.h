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
		virtual ~Field();

		void Render3D() override;

	private:

		ID3D11Buffer* _vertex_buffer;

		TexturePtr _texture;

		VertexShaderPtr _vertex_shader;

		PixelShaderPtr _pixel_shader;

		Field();
		Field(const Field&) = delete;
		Field& operator=(const Field&) = delete;

		friend class Component;
	};

	typedef std::shared_ptr<Field> FieldPtr;
}

#endif //!_FIELD_H_
