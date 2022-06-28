

#ifdef DIRECTX11

#include "Common/ExtraX.h"
#include "Common/Graphics.h"
#include "Common/Asset.h"
#include "Common/Input.h"
#include "Common/Window.h"
#include "Common/Timer.h"
#include "Common/Math.h"

#include <wrl.h>
#include <d3d11.h>
#include <dxgi1_6.h>
#include <windows.h>

using namespace XX::Math;

using namespace DirectX;


HWND GetWindowsHWND(XX::Window* window);

using Microsoft::WRL::ComPtr;

static D3D_FEATURE_LEVEL  feature_level = D3D_FEATURE_LEVEL_11_1;

static ComPtr<IDXGIFactory7> factory;

static ComPtr<ID3D11Device> device;

static ComPtr<ID3D11DeviceContext> immediate_context;

static ComPtr<ID3D11DeviceContext> deferred_context[THREAD_NUM];

static ComPtr<ID3D11CommandList> command_list[THREAD_NUM];

static ComPtr<IDXGISwapChain> swap_chain;

static ComPtr<ID3D11RenderTargetView> render_target_view;

static ComPtr<ID3D11DepthStencilView> depth_stencil_view;

static ComPtr<ID3D11DepthStencilView> shadow_depth_stencil_view;

static ComPtr<ID3D11ShaderResourceView> shadow_shader_resource_view;

static ComPtr<ID3D11RasterizerState> rasterizer_state;

static ComPtr<ID3D11BlendState> blend_state;

static ComPtr<ID3D11DepthStencilState> depth_state_enable;

static ComPtr<ID3D11DepthStencilState> depth_state_disable;

static ComPtr<ID3D11SamplerState> sampler_state;

static ComPtr<ID3D11Buffer> view_buffer_2d;

static ComPtr<ID3D11Buffer> projection_buffer_2d;

static ComPtr<ID3D11Buffer> view_buffer;

static ComPtr<ID3D11Buffer> projection_buffer;

static ComPtr<ID3D11Buffer> world_buffer;

static ComPtr<ID3D11Buffer> texcoord_offset_buffer;

static ComPtr<ID3D11Buffer> material_buffer;

static ComPtr<ID3D11Buffer> light_buffer;

static ComPtr<ID3D11Buffer> camera_parameter_buffer;

static ComPtr<ID3D11Buffer> extra_parameter_buffer;


void InitialzeDX11()
{

	//クリエイトファクトリー
	CreateDXGIFactory2(0, __uuidof(IDXGIFactory2), (void**)factory.GetAddressOf());

	//クリエイトディバイスと即時コンテキスト
	D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		device.GetAddressOf(),
		&feature_level,
		immediate_context.GetAddressOf()
	);

	//クリエイト遅延コンテキスト
	for (auto& i : deferred_context)
	{
		device->CreateDeferredContext(0, i.GetAddressOf());
	}

	//クリエイトスワップチェーン
	DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
	swap_chain_desc.BufferCount = 3;
	swap_chain_desc.Width = XX::ExtraX::window->GetWidth();
	swap_chain_desc.Height = XX::ExtraX::window->GetHeight();
	swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_chain_desc.SampleDesc.Count = 1;
	factory->CreateSwapChainForHwnd(device.Get(), GetWindowsHWND(XX::ExtraX::window), &swap_chain_desc, NULL, NULL, (IDXGISwapChain1**)swap_chain.GetAddressOf());

	ComPtr<ID3D11Texture2D> render_target;
	swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)render_target.GetAddressOf());
	device->CreateRenderTargetView(render_target.Get(), nullptr, render_target_view.GetAddressOf());

	D3D11_TEXTURE2D_DESC texture_desc = {};
	ComPtr<ID3D11Texture2D> depth_stencil;
	texture_desc.Width = swap_chain_desc.Width;
	texture_desc.Height = swap_chain_desc.Height;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_D16_UNORM;
	texture_desc.SampleDesc = swap_chain_desc.SampleDesc;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	device->CreateTexture2D(&texture_desc, NULL, depth_stencil.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc = {};
	depth_stencil_view_desc.Format = texture_desc.Format;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Flags = 0;
	device->CreateDepthStencilView(depth_stencil.Get(), &depth_stencil_view_desc, depth_stencil_view.GetAddressOf());
	immediate_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());


	//シャドー
	ComPtr<ID3D11Texture2D> shadow_depth;
	texture_desc.Width = swap_chain_desc.Width;
	texture_desc.Height = swap_chain_desc.Height;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_R32_TYPELESS;
	texture_desc.SampleDesc = swap_chain_desc.SampleDesc;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;;
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	device->CreateTexture2D(&texture_desc, NULL, shadow_depth.GetAddressOf());

	depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Flags = 0;
	device->CreateDepthStencilView(shadow_depth.Get(), &depth_stencil_view_desc, shadow_depth_stencil_view.GetAddressOf());
	
	D3D11_SHADER_RESOURCE_VIEW_DESC shadwe_resource_view_desc = {};
	shadwe_resource_view_desc.Format = DXGI_FORMAT_R32_FLOAT;
	shadwe_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shadwe_resource_view_desc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(shadow_depth.Get(), &shadwe_resource_view_desc, shadow_shader_resource_view.GetAddressOf());

	// ビューポート設定
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)XX::ExtraX::window->GetWidth();
	viewport.Height = (float)XX::ExtraX::window->GetHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	immediate_context->RSSetViewports(1, &viewport);

	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rasterizer_desc = {};
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_BACK;
	rasterizer_desc.DepthClipEnable = TRUE;
	rasterizer_desc.MultisampleEnable = FALSE;
	device->CreateRasterizerState(&rasterizer_desc, rasterizer_state.GetAddressOf());
	immediate_context->RSSetState(rasterizer_state.Get());

	// ブレンドステート設定
	D3D11_BLEND_DESC blend_desc = {};
	blend_desc.AlphaToCoverageEnable = TRUE;
	blend_desc.IndependentBlendEnable = TRUE;
	blend_desc.RenderTarget[0].BlendEnable = TRUE;
	blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blend_factor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	device->CreateBlendState(&blend_desc, blend_state.GetAddressOf());
	immediate_context->OMSetBlendState(blend_state.Get(), blend_factor, 0xffffffff);


	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc = {};
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depth_stencil_desc.StencilEnable = FALSE;
	device->CreateDepthStencilState(&depth_stencil_desc, depth_state_enable.GetAddressOf());//深度有効ステート
	depth_stencil_desc.DepthEnable = FALSE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	device->CreateDepthStencilState(&depth_stencil_desc, depth_state_disable.GetAddressOf());//深度無効ステート
	immediate_context->OMSetDepthStencilState(depth_state_enable.Get(), NULL);

	// サンプラーステート設定
	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	sampler_desc.MaxAnisotropy = 16;
	device->CreateSamplerState(&sampler_desc, sampler_state.GetAddressOf());
	immediate_context->PSSetSamplers(0, 1, sampler_state.GetAddressOf());

	// 定数バッファ生成
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Matrix);
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(float);

	device->CreateBuffer(&buffer_desc, NULL, view_buffer_2d.GetAddressOf());
	immediate_context->VSSetConstantBuffers(0, 1, view_buffer_2d.GetAddressOf());

	device->CreateBuffer(&buffer_desc, NULL, projection_buffer_2d.GetAddressOf());
	immediate_context->VSSetConstantBuffers(1, 1, projection_buffer_2d.GetAddressOf());

	device->CreateBuffer(&buffer_desc, NULL, view_buffer.GetAddressOf());
	immediate_context->VSSetConstantBuffers(2, 1, view_buffer.GetAddressOf());

	device->CreateBuffer(&buffer_desc, NULL, projection_buffer.GetAddressOf());
	immediate_context->VSSetConstantBuffers(3, 1, projection_buffer.GetAddressOf());

	device->CreateBuffer(&buffer_desc, NULL, world_buffer.GetAddressOf());
	immediate_context->VSSetConstantBuffers(4, 1, world_buffer.GetAddressOf());

	buffer_desc.ByteWidth = 16; //sizeof(XX::Math::Float2);
	device->CreateBuffer(&buffer_desc, NULL, texcoord_offset_buffer.GetAddressOf());
	immediate_context->VSSetConstantBuffers(6, 1, texcoord_offset_buffer.GetAddressOf());

	buffer_desc.ByteWidth = 16; //sizeof(XX::Material);
	device->CreateBuffer(&buffer_desc, NULL, material_buffer.GetAddressOf());
	immediate_context->PSSetConstantBuffers(7, 1, material_buffer.GetAddressOf());

	buffer_desc.ByteWidth = 16; //sizeof(XX::Light);
	device->CreateBuffer(&buffer_desc, NULL, light_buffer.GetAddressOf());
	immediate_context->PSSetConstantBuffers(8, 1, light_buffer.GetAddressOf());

	buffer_desc.ByteWidth = 16; //sizeof(XX::CameraParameter);
	device->CreateBuffer(&buffer_desc, NULL, camera_parameter_buffer.GetAddressOf());
	immediate_context->PSSetConstantBuffers(9, 1, camera_parameter_buffer.GetAddressOf());

	buffer_desc.ByteWidth = 16; //sizeof(XX::ExtraParameter);
	device->CreateBuffer(&buffer_desc, NULL, extra_parameter_buffer.GetAddressOf());
	immediate_context->PSSetConstantBuffers(10, 1, extra_parameter_buffer.GetAddressOf());

	//定数バッファ初期値を設定
	XX::Math::Matrix view2d = XMMatrixIdentity();
	view2d = DirectX::XMMatrixTranspose(view2d);
	immediate_context->UpdateSubresource(view_buffer_2d.Get(), 0, NULL, &view2d, 0, 0);

	DirectX::XMMATRIX projection2d;
	projection2d = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, (FLOAT)swap_chain_desc.Width, (FLOAT)swap_chain_desc.Height, 0.0f, 0.0f, 1.0f);
	projection2d = DirectX::XMMatrixTranspose(projection2d);
	immediate_context->UpdateSubresource(projection_buffer_2d.Get(), 0, NULL, &projection2d, 0, 0);

	Float2 offset(0.0f, 0.0f);
	immediate_context->UpdateSubresource(texcoord_offset_buffer.Get(), 0, NULL, &offset, 0, 0);
		
}

class ShaderDX11 : public XX::_Shader
{
	friend class XX::AssetImporter;

private:
	ComPtr<ID3D11InputLayout> _input_layout;

	ComPtr<ID3D11VertexShader> _vertex_shader;

	ComPtr<ID3D11PixelShader> _pixel_shader;

public:
	void Set(size_t thread) override
	{
		deferred_context[thread]->IASetInputLayout(_input_layout.Get());
		deferred_context[thread]->VSSetShader(_vertex_shader.Get(), NULL, 0);
		deferred_context[thread]->PSSetShader(_pixel_shader.Get(), NULL, 0);
	}
};

class MeshDX11 : public XX::_Mesh
{
	friend class XX::Graphics;
private:
	UINT _vertices_num;
	ComPtr<ID3D11Buffer> _vertices_buffer;
	UINT _indices_num;
	ComPtr<ID3D11Buffer> _indices_buffer;

public:
	void Set(size_t thread) override
	{
		UINT stride = sizeof(XX::Vertex);
		UINT offset = 0;
		deferred_context[thread]->IASetVertexBuffers(0, 1, _vertices_buffer.GetAddressOf(), &stride, &offset);
		deferred_context[thread]->IASetIndexBuffer(_indices_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		deferred_context[thread]->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deferred_context[thread]->DrawIndexed(_indices_num, 0, 0);
	}
};



namespace XX
{
	

	void Graphics::Begin() const
	{
		immediate_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());
		float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		immediate_context->ClearRenderTargetView(render_target_view.Get(), ClearColor);
		immediate_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void Graphics::End() const
	{
		for (auto& i : command_list)
		{
			immediate_context->ExecuteCommandList(i.Get(), FALSE);
			i->Release();
		}
		swap_chain->Present(1, 0);
	}

	void Graphics::BeginRenderShadow() const
	{
		immediate_context->OMSetRenderTargets(0, NULL, shadow_depth_stencil_view.Get());
		immediate_context->ClearDepthStencilView(shadow_depth_stencil_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void Graphics::EndRenderShadow() const 
	{
		for (auto& i : command_list)
		{
			immediate_context->ExecuteCommandList(i.Get(), FALSE);
		}

		immediate_context->PSSetShaderResources(1, 1, shadow_shader_resource_view.GetAddressOf());
	}

	void Graphics::FinishCommandList(size_t thread) const
	{
		deferred_context[thread]->FinishCommandList(FALSE, command_list[thread].GetAddressOf());
	}

	void Graphics::SetDepthEnable(bool enable, size_t thread) const
	{
		if (enable)
			deferred_context[thread]->OMSetDepthStencilState(depth_state_enable.Get(), NULL);
		else
			deferred_context[thread]->OMSetDepthStencilState(depth_state_disable.Get(), NULL);
	}

	void Graphics::SetWorldMatrix(const Matrix* world_matrix, size_t thread) const
	{
		Matrix matrix = XMMatrixTranspose(*world_matrix);
		deferred_context[thread]->UpdateSubresource(world_buffer.Get(), 0, NULL, &matrix, 0, 0);
	}

	void Graphics::SetViewMatrix(const Matrix* view_matrix, size_t thread) const
	{
		Matrix matrix = XMMatrixTranspose(*view_matrix);
		deferred_context[thread]->UpdateSubresource(view_buffer.Get(), 0, NULL, &matrix, 0, 0);
	}

	void Graphics::SetProjectionMatrix(const Matrix* projection_matrix, size_t thread) const
	{
		Matrix matrix = XMMatrixTranspose(*projection_matrix);
		deferred_context[thread]->UpdateSubresource(projection_buffer.Get(), 0, NULL, &matrix, 0, 0);
	}

	Mesh Graphics::CreateMesh(std::vector<Vertex>& vertices, std::vector<Index>& indices) const
	{
		MeshDX11* new_mesh = new MeshDX11;

		new_mesh->_vertices_num = (UINT)vertices.size();
		D3D11_BUFFER_DESC vbd{};
		vbd.Usage = D3D11_USAGE_DYNAMIC;
		vbd.ByteWidth = sizeof(Vertex) * new_mesh->_vertices_num;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		D3D11_SUBRESOURCE_DATA vsd{};
		vsd.pSysMem = vertices.data();
		device->CreateBuffer(&vbd, &vsd, new_mesh->_vertices_buffer.GetAddressOf());


		new_mesh->_indices_num = (UINT)indices.size();
		D3D11_BUFFER_DESC ibd{};
		ibd.Usage = D3D11_USAGE_DYNAMIC;
		ibd.ByteWidth = sizeof(UINT) * new_mesh->_indices_num;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		D3D11_SUBRESOURCE_DATA isd{};
		isd.pSysMem = indices.data();
		device->CreateBuffer(&ibd, &isd, new_mesh->_indices_buffer.GetAddressOf());

		return Mesh(new_mesh);
	}

	
	//===========================================================================================================//

	Texture AssetImporter::ImportTexture(const std::string& file)
	{
		return 0;
	}

	Model AssetImporter::ImportModel(const std::string& file)
	{
		return 0;
	}

	Shader AssetImporter::ImportShader(const std::string& file)
	{
		auto iter = _shaders.find(file);
		if (iter != _shaders.end())
		{
			return iter->second;
		}

		ShaderDX11* new_shader = new ShaderDX11;

		std::ifstream shader_file;
		shader_file.open(file, std::ios::binary | std::ios::in);

		size_t element_num = 0;
		shader_file.read(reinterpret_cast<char*>(&element_num), sizeof(element_num));

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[element_num];
		shader_file.read(reinterpret_cast<char*>(layout), sizeof(D3D11_INPUT_ELEMENT_DESC) * element_num);
		for (size_t i = 0; i < element_num; ++i)
		{
			size_t length = 0;
			shader_file.read(reinterpret_cast<char*>(&length), sizeof(length));
			char* name = new char[length];
			shader_file.read(reinterpret_cast<char*>(name), length);
			layout[i].SemanticName = name;
		}

		size_t vertex_shader_size = 0;
		shader_file.read(reinterpret_cast<char*>(&vertex_shader_size), sizeof(vertex_shader_size));
		char* vs = new char[vertex_shader_size];
		shader_file.read(vs, vertex_shader_size);

		size_t pixel_shader_size = 0;
		shader_file.read(reinterpret_cast<char*>(&pixel_shader_size), sizeof(pixel_shader_size));
		char* ps = new char[pixel_shader_size];
		shader_file.read(ps, pixel_shader_size);

		device->CreateInputLayout(layout, (UINT)element_num, vs, vertex_shader_size, new_shader->_input_layout.GetAddressOf());
		device->CreateVertexShader(vs, vertex_shader_size, NULL, new_shader->_vertex_shader.GetAddressOf());
		device->CreatePixelShader(ps, pixel_shader_size, NULL, new_shader->_pixel_shader.GetAddressOf());

		Shader shader(new_shader);

		_shaders[file] = shader;

		for (size_t i = 0; i < element_num; ++i)
		{
			delete[] reinterpret_cast<const char*>(layout[i].SemanticName);
		}
		delete[] layout;
		delete[] vs;
		delete[] ps;
		shader_file.close();

		return shader;
	}


	//===========================================================================================================//

	void ExtraX::Initialize(const std::string& title)
	{
		_input = new Input();
		_window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, title);
		InitialzeDX11();
		_graphics = new Graphics();
		_asset_importer = new AssetImporter();
		_timer = new Timer();
	}

}


#endif // DIRECTX11
