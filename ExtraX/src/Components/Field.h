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
	/*====================コンストラクターとデストラクター====================*/
	public:
		virtual ~Field() = default;
	private:
		Field(int row, int column, const std::string texture_file = DEFAULT_TEXTRUE);
		Field(const Field&) = delete;
		Field& operator=(const Field&) = delete;
	
	/*================================メンバー================================*/
	private:
		int _row;
		int _column;
		VertexShaderPtr _vertex_shader;
		PixelShaderPtr _pixel_shader;
		MeshPtr _mesh;
		XXMaterial _material;

	/*================================メソッド================================*/
	public:
		void Render3D() override;

	/*================================フレンド================================*/
		friend class Component;
	};

	typedef std::shared_ptr<Field> FieldPtr;
}

#endif //!_FIELD_H_
