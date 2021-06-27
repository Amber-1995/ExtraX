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
	std::wstring w_file_name = StringHelper::ToWide(file_name);

	DirectX::ScratchImage image_data;
	HRESULT ret = DirectX::LoadFromWICFile(w_file_name.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(ret)) {
		ret = DirectX::CreateTexture(
			ExtraX::graphics.device,
			image_data.GetImages(),
			image_data.GetImageCount(),
			image_data.GetMetadata(),
			_texture_resource.GetAddressOf()
		);
	}
	else {
		MessageBox(nullptr, "Textrue load failure!", "error", MB_OK);
		exit(-1);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format = image_data.GetMetadata().format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
	desc.Texture2D.MostDetailedMip = 0;
	ExtraX::graphics.device->CreateShaderResourceView(_texture_resource.Get(), &desc, _texture.GetAddressOf());
	
}






