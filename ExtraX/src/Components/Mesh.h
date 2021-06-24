#pragma once
#ifndef _MESH_H_
#define _MESH_H_
#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"
#include <string>

namespace XX
{
	
	class Mesh : public Component,public IRender3D
	{
	public:
		void Render3D() override;

		void AdjustTransform(
			XXVector3 pos_offset,
			XXVector3 rot_offset,
			XXVector3 scl_oofset
		);

	private:
		ModelPtr _model;

		VertexShaderPtr _vertex_shader;

		PixelShaderPtr _pixel_shader;

		DirectX::XMMATRIX _adj_matrix;

		Mesh(std::string file_name);
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		friend class Component;

	};

	typedef std::shared_ptr<Mesh> MeshPtr;
}






#endif // !_MESH_H_

