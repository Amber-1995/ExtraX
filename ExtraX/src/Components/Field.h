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
		int _row;

		int _column;

		ID3D11BufferPtr _vertex_buffer;

		ID3D11BufferPtr _index_buffer;

		TexturePtr _texture;

		VertexShaderPtr _vertex_shader;

		PixelShaderPtr _pixel_shader;

		Field(int row, int column, const std::string texture_file = DEFAULT_TEXTRUE);
		Field(const Field&) = delete;
		Field& operator=(const Field&) = delete;

		friend class Component;
	};

	typedef std::shared_ptr<Field> FieldPtr;
}

#endif //!_FIELD_H_
