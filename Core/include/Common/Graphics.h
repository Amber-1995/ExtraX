#ifndef CORE_GRAPHICS_H
#define CORE_GRAPHICS_H


#include "ExtraX.h"


namespace XX
{
	using Index = uint32_t;

	struct Vertex
	{
		Float3 position;
		Float3 normal;
		Float4 diffuse;
		Float2 tex_coord;
	};

	struct Material
	{

	};

	struct Light
	{

	};

	struct CameraParameter
	{

	};

	struct ExtraParameter
	{

	};

	class _Mesh
	{
	public:
		virtual void Set(size_t thread) = 0;
	};

	using Mesh = std::shared_ptr<_Mesh>;


	class Graphics
	{
		friend class ExtraX;
	private:
		float _width = WINDOW_WIDTH;

		float _height = WINDOW_HEIGHT;

	public:
		const float& width = _width;

		const float& height = _height;

		void Begin() const;

		void End() const;

		void BeginRenderShadow() const;

		void EndRenderShadow() const;

		void FinishCommandList(size_t thread) const;

		void SetDepthEnable(bool Enable, size_t thread) const;

		void SetViewMatrix(const Matrix* view_matrix, size_t thread) const;

		void SetProjectionMatrix(const Matrix* projection_matrix, size_t thread) const;

		void SetWorldMatrix(const Matrix* world_matrix, size_t thread) const;

		Mesh CreateMesh(std::vector<Vertex>& vertices, std::vector<Index>& indices) const;

	private:
		Graphics() = default;

		virtual ~Graphics() = default;
	};
}

#endif // !CORE_GRAPHICS_H

