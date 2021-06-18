#include "Graphics.h"
#include <stdio.h>
#include <assert.h>
#include <io.h>

void XX::Graphics::Init(HWND window, int width, int height)
{
	_width = width;
	_height = height;

	HRESULT hr = S_OK;

	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swap_chain,
		&_device,
		&_feature_level,
		&_device_context);

	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget = NULL;
	_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	_device->CreateRenderTargetView(renderTarget, NULL, &_render_target_view);
	renderTarget->Release();

	// デプスステンシルバッファ作成
	ID3D11Texture2D* depthStencile = NULL;
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	_device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	_device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &_depth_stencil_view);
	//depthStencile->Release();
	_device_context->OMSetRenderTargets(1, &_render_target_view, _depth_stencil_view);

	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	_device_context->RSSetViewports(1, &viewport);

	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	_device->CreateRasterizerState(&rasterizerDesc, &rs);
	_device_context->RSSetState(rs);


	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	_device->CreateBlendState(&blendDesc, &blendState);
	_device_context->OMSetBlendState(blendState, blendFactor, 0xffffffff);



	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	_device->CreateDepthStencilState(&depthStencilDesc, &_depth_state_enable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	_device->CreateDepthStencilState(&depthStencilDesc, &_depth_state_disable);//深度無効ステート

	_device_context->OMSetDepthStencilState(_depth_state_enable, NULL);




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	ID3D11SamplerState* samplerState = NULL;
	_device->CreateSamplerState(&samplerDesc, &samplerState);
	_device_context->PSSetSamplers(0, 1, &samplerState);



	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	_device->CreateBuffer(&bufferDesc, NULL, &_world_buffer);
	_device_context->VSSetConstantBuffers(0, 1, &_world_buffer);

	_device->CreateBuffer(&bufferDesc, NULL, &_view_buffer);
	_device_context->VSSetConstantBuffers(1, 1, &_view_buffer);

	_device->CreateBuffer(&bufferDesc, NULL, &_projection_buffer);
	_device_context->VSSetConstantBuffers(2, 1, &_projection_buffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);
	_device->CreateBuffer(&bufferDesc, NULL, &_material_buffer);
	_device_context->VSSetConstantBuffers(3, 1, &_material_buffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);
	_device->CreateBuffer(&bufferDesc, NULL, &_light_buffer);
	_device_context->VSSetConstantBuffers(4, 1, &_light_buffer);
	_device_context->PSSetConstantBuffers(4, 1, &_light_buffer);


	// ライト初期化
	LIGHT light{};
	light.enable = true;
	light.direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.direction, &light.direction);
	light.ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetLight(light);

	// マテリアル初期化
	MATERIAL material{};
	material.diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

}

XX::Graphics::~Graphics()
{
	_world_buffer->Release();
	_view_buffer->Release();
	_projection_buffer->Release();
	_light_buffer->Release();
	_material_buffer->Release();


	_device_context->ClearState();
	_render_target_view->Release();
	_swap_chain->Release();
	_device_context->Release();
	_device->Release();
}

void XX::Graphics::Begin() const
{
	float clearColor[4] = { 0.3f, 0.2f, 0.6f, 1.0f };
	_device_context->ClearRenderTargetView(_render_target_view, clearColor);
	_device_context->ClearDepthStencilView(_depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void XX::Graphics::End() const
{
	_swap_chain->Present(1, 0);
}

void XX::Graphics::SetDepthEnable(bool enable) const
{
	if (enable)
		_device_context->OMSetDepthStencilState(_depth_state_enable, NULL);
	else
		_device_context->OMSetDepthStencilState(_depth_state_disable, NULL);
}

void XX::Graphics::SetWorldViewProjection2D() const
{
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	world = DirectX::XMMatrixTranspose(world);
	_device_context->UpdateSubresource(_world_buffer, 0, nullptr, &world, 0, 0);

	DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
	view = DirectX::XMMatrixTranspose(view);
	_device_context->UpdateSubresource(_view_buffer, 0, nullptr, &view, 0, 0);

	DirectX::XMMATRIX projection;
	projection = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, (FLOAT)_width, (FLOAT)_height, 0.0f, 0.0f, 1.0f);
	projection = DirectX::XMMatrixTranspose(projection);
	_device_context->UpdateSubresource(_projection_buffer, 0, NULL, &projection, 0, 0);
}

void XX::Graphics::SetWorldMatrix(const DirectX::XMMATRIX& world_matrix) const
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranspose(world_matrix);
	_device_context->UpdateSubresource(_world_buffer, 0, NULL, &matrix, 0, 0);
}

void XX::Graphics::SetViewMatrix(const DirectX::XMMATRIX& view_matrix) const
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranspose(view_matrix);
	_device_context->UpdateSubresource(_view_buffer, 0, NULL, &matrix, 0, 0);
}

void XX::Graphics::SetProjectionMatrix(const DirectX::XMMATRIX& projection_matrix) const
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranspose(projection_matrix);
	_device_context->UpdateSubresource(_projection_buffer, 0, NULL, &matrix, 0, 0);
}

void XX::Graphics::SetMaterial(MATERIAL material) const
{
	_device_context->UpdateSubresource(_material_buffer, 0, NULL, &material, 0, 0);
}

void XX::Graphics::SetLight(LIGHT light) const
{
	_device_context->UpdateSubresource(_light_buffer, 0, NULL, &light, 0, 0);
}

void XX::Graphics::CreateVertexShader(ID3D11VertexShader** vertex_shader, ID3D11InputLayout** vertex_layout, const char* file_name) const
{
	FILE* file;
	long int fsize;

	file = fopen(file_name, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	_device->CreateVertexShader(buffer, fsize, NULL, vertex_shader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	_device->CreateInputLayout(
		layout,
		numElements,
		buffer,
		fsize,
		vertex_layout
	);

	delete[] buffer;
}

void XX::Graphics::CreatePixelShader(ID3D11PixelShader** pixel_shader, const char* file_name) const
{
	FILE* file;
	long int fsize;

	file = fopen(file_name, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	_device->CreatePixelShader(buffer, fsize, NULL, pixel_shader);

	delete[] buffer;
}

XX::Graphics::Graphics() :
	device(_device),
	device_context(_device_context),
	width(_width),
	height(_height),
	_width(0),
	_height(0),
	_feature_level(D3D_FEATURE_LEVEL_11_0),
	_device(nullptr),
	_device_context(nullptr),
	_swap_chain(nullptr),
	_render_target_view(nullptr),
	_depth_stencil_view(nullptr),
	_world_buffer(nullptr),
	_view_buffer(nullptr),
	_projection_buffer(nullptr),
	_material_buffer(nullptr),
	_light_buffer(nullptr),
	_depth_state_enable(nullptr),
	_depth_state_disable(nullptr)
{

}
