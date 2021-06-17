#include "Shader.h"
#include "../XX.h"




void XX::VertexShader::Apply()
{
	ExtraX::graphics.device_context->IASetInputLayout(_vertex_layout);
	ExtraX::graphics.device_context->VSSetShader(_vertex_shader, nullptr, 0);
}

XX::VertexShader::VertexShader(const std::string& file_name)
{
	ExtraX::graphics.CreateVertexShader(&_vertex_shader, &_vertex_layout, file_name.c_str());
}



void XX::PixelShader::Apply()
{
	ExtraX::graphics.device_context->PSSetShader(_pixel_shader, nullptr, 0);
}

XX::PixelShader::PixelShader(const std::string& file_name)
{
	ExtraX::graphics.CreatePixelShader(&_pixel_shader, "Assets\\Shaders\\unlitTexturePS.cso");
}
