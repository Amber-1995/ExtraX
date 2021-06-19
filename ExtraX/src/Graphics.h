#pragma once
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Data/Data.h"

namespace XX
{

	class Graphics
	{
	friend class ExtraX;

	public:

		ID3D11Device* const& device;

		ID3D11DeviceContext* const& device_context;

		const int& width;

		const int& height;


		void Init(HWND window, int width, int height);

		virtual ~Graphics() = default;

		void Begin() const;

		void End() const;

		void SetDepthEnable(bool enable) const;

		void SetWorldViewProjection2D() const;

		void SetWorldMatrix(const DirectX::XMMATRIX& world_matrix) const;

		void SetViewMatrix(const DirectX::XMMATRIX& view_matrix) const;

		void SetProjectionMatrix(const DirectX::XMMATRIX& projection_matrix) const;

		void SetMaterial(XXMaterial material) const;

		void SetLight(XXLight light) const;

		void CreateVertexShader(ID3D11VertexShader** vertex_shader, ID3D11InputLayout** vertex_layout, const char* file_name) const;

		void CreatePixelShader(ID3D11PixelShader** pixel_shader, const char* file_name) const;


	private:
		int _width;

		int _height;

		D3D_FEATURE_LEVEL  _feature_level;

		ID3D11DevicePtr _device;

		ID3D11DeviceContextPtr _device_context;

		IDXGISwapChainPtr _swap_chain;

		ID3D11RenderTargetViewPtr _render_target_view;

		ID3D11DepthStencilViewPtr _depth_stencil_view;

		ID3D11BufferPtr _world_buffer;

		ID3D11BufferPtr _view_buffer;

		ID3D11BufferPtr _projection_buffer;

		ID3D11BufferPtr _material_buffer;

		ID3D11BufferPtr _light_buffer;

		ID3D11DepthStencilStatePtr _depth_state_enable;

		ID3D11DepthStencilStatePtr _depth_state_disable;

		Graphics();
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		
	};

}

#endif // !_GRAPHICS_H_

