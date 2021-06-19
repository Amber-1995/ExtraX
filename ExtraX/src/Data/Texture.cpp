#include "Texture.h"
#include "../XX.h"
#include <DirectXTex/DirectXTex.h>





void XX::Texture::Apply()
{
	ExtraX::graphics.device_context->PSSetShaderResources(0, 1, _texture.GetAddressOf());
}


XX::Texture::Texture(const std::string& file_name):
	_texture(nullptr)
{
	wchar_t w_file_name[1024];
	mbstowcs_s(nullptr, w_file_name, file_name.c_str(), _TRUNCATE);

	DirectX::ScratchImage image_data;
	HRESULT ret = DirectX::LoadFromWICFile(w_file_name, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(ret)) {
		ret = DirectX::CreateTexture(
			ExtraX::graphics.device,
			image_data.GetImages(),
			image_data.GetImageCount(),
			image_data.GetMetadata(),
			_texture_resource.GetAddressOf()
		);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format = image_data.GetMetadata().format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
	desc.Texture2D.MostDetailedMip = 0;
	ExtraX::graphics.device->CreateShaderResourceView(_texture_resource.Get(), &desc, _texture.GetAddressOf());
	
}






