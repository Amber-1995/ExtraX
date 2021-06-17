#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Resource.h"

namespace XX
{
	class VertexShader :public Resource<VertexShader>
	{
	public:
		void Apply() override;

	private:
		ID3D11VertexShader* _vertex_shader;

		ID3D11InputLayout* _vertex_layout;

		VertexShader(const std::string& file_name);

		virtual ~VertexShader() = default;
	
		friend class Resource<VertexShader>;
	};

	class PixelShader : public Resource<PixelShader>
	{
	public:
		void Apply() override;

	private:
		ID3D11PixelShader* _pixel_shader;

		PixelShader(const std::string& file_name);

		virtual ~PixelShader() = default;

		friend class Resource<PixelShader>;

	};

	std::map<std::string, VertexShader*> VertexShader::_resources;
	std::map<std::string, PixelShader*> PixelShader::_resources;
}



#endif // !_SHADER_H_
