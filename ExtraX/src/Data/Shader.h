#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Resource.h"
#include "ExtraXType.h"

namespace XX
{
	class VertexShader : public Resource<VertexShader>
	{
	public:
		void Apply() override;

		virtual ~VertexShader() = default;
	private:
		ID3D11VertexShaderPtr _vertex_shader;

		ID3D11InputLayoutPtr _vertex_layout;

		VertexShader(const std::string& file_name);

		
	
		friend class Resource<VertexShader>;
	};

	typedef std::shared_ptr<VertexShader> VertexShaderPtr;
	std::unordered_map<std::string, VertexShaderPtr> VertexShader::_resources;


	class PixelShader : public Resource<PixelShader>
	{
	public:
		void Apply() override;

		virtual ~PixelShader() = default;
	private:
		ID3D11PixelShaderPtr _pixel_shader;

		PixelShader(const std::string& file_name);

		friend class Resource<PixelShader>;

	};

	typedef std::shared_ptr<PixelShader> PixelShaderPtr;
	std::unordered_map<std::string, PixelShaderPtr> PixelShader::_resources;
}



#endif // !_SHADER_H_
