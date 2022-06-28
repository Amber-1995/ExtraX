#include <fstream>
#include <d3d11.h>
#include <iostream>


#define VERTEX_SHADER "2DVS.cso"
#define PIXEL_SHADER "2DPS.cso"
#define XX_SHADER "..\\Core\\Assets\\Shader\\2D.XXShader"
#define ELEMENT_NUM (4)

int main()
{
	std::ifstream vertex_shader;
	vertex_shader.open(VERTEX_SHADER, std::ios::binary | std::ios::in);

	std::ifstream pixel_shader;
	pixel_shader.open(PIXEL_SHADER, std::ios::binary | std::ios::in);

	std::ofstream xx_shader;
	xx_shader.open(XX_SHADER, std::ios::binary | std::ios::out | std::ios::trunc);


	size_t element_num = ELEMENT_NUM;

	vertex_shader.seekg(0, vertex_shader.end);
	size_t vertex_shader_size = vertex_shader.tellg();
	char* vs = new char[vertex_shader_size];
	vertex_shader.seekg(0, vertex_shader.beg);
	vertex_shader.read(vs, vertex_shader_size);

	pixel_shader.seekg(0, pixel_shader.end);
	size_t pixel_shader_size = pixel_shader.tellg();
	char* ps = new char[pixel_shader_size];
	vertex_shader.seekg(0, pixel_shader.beg);
	vertex_shader.read(ps, pixel_shader_size);

	D3D11_INPUT_ELEMENT_DESC layout[ELEMENT_NUM] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0     , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 4 * 3 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      , 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	xx_shader.write(reinterpret_cast<char*>(&element_num), sizeof(element_num));
	xx_shader.write(reinterpret_cast<char*>(layout), sizeof(layout));
	for (int64_t i = 0; i < element_num; ++i)
	{
		size_t length = strlen(layout[i].SemanticName) + 1;
		xx_shader.write(reinterpret_cast<char*>(&length), sizeof(length));
		xx_shader.write(layout[i].SemanticName, length);
	}

	xx_shader.write(reinterpret_cast<char*>(&vertex_shader_size), sizeof(vertex_shader_size));
	xx_shader.write(vs, vertex_shader_size);

	xx_shader.write(reinterpret_cast<char*>(&pixel_shader_size), sizeof(pixel_shader_size));
	xx_shader.write(ps, pixel_shader_size);


	delete[] vs;
	delete[] ps;
	vertex_shader.close();
	pixel_shader.close();
	xx_shader.close();

	
}