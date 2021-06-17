#include "Texture.h"
#include "../XX.h"




void XX::Texture::Apply()
{
	ExtraX::graphics.device_context->PSSetShaderResources(0, 1, &_texture);
}


XX::Texture::Texture(const std::string& file_name):
	_texture(nullptr)
{
	D3DX11CreateShaderResourceViewFromFile(
		ExtraX::graphics.device,
		file_name.c_str(),
		nullptr,
		nullptr,
		&_texture,
		nullptr
	);

	assert(_texture);
}




