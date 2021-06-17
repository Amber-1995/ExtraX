#pragma once
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#pragma warning(push)
#pragma warning(disable:4005)
#include <d3d11.h>
#pragma warning(pop)

#include "Data/ExtraXType.h"

namespace XX
{

	class Graphics
	{
	friend class ExtraX;

	public:

		ID3D11Device* const& device;

		ID3D11DeviceContext* const& device_context;

		void Init(HWND window, int width, int height);

		virtual ~Graphics();

		void Begin() const;

		void End() const;

		void SetDepthEnable(bool enable) const;

		void SetWorldViewProjection2D() const;
	

		void SetWorldMatrix(D3DXMATRIX* world_matrix) const;
	
		void SetViewMatrix(D3DXMATRIX* view_matrix) const;
	
		void SetProjectionMatrix(D3DXMATRIX* projection_matrix) const;

		void SetMaterial(MATERIAL material) const;

		void SetLight(LIGHT light) const;

		void CreateVertexShader(ID3D11VertexShader** vertex_shader, ID3D11InputLayout** vertex_layout, const char* file_name) const;

		void CreatePixelShader(ID3D11PixelShader** pixel_shader, const char* file_name) const;


	private:
		int _width;

		int _height;

		D3D_FEATURE_LEVEL  _feature_level;

		ID3D11Device* _device;

		ID3D11DeviceContext* _device_context;

		IDXGISwapChain* _swap_chain;

		ID3D11RenderTargetView* _render_target_view;

		ID3D11DepthStencilView* _depth_stencil_view;

		ID3D11Buffer* _world_buffer;

		ID3D11Buffer* _view_buffer;

		ID3D11Buffer* _projection_buffer;

		ID3D11Buffer* _material_buffer;

		ID3D11Buffer* _light_buffer;

		ID3D11DepthStencilState* _depth_state_enable;

		ID3D11DepthStencilState* _depth_state_disable;

		Graphics();
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		
	};

}

#endif // !_GRAPHICS_H_

