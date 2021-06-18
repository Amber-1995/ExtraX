#include "Texture.h"
#include "../XX.h"
#include <D3DX11.h>





std::wstring ToWide(const std::string& narrow)
{
	wchar_t wide[512];
	mbstowcs_s(nullptr, wide, narrow.c_str(), _TRUNCATE);
	return wide;
}

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




