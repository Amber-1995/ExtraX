#pragma once
#ifndef EXTRAX_SHADER_BASE_H
#define EXTRAX_SHADER_BASE_H

#include <ExtraX/Common.h>
#include <ExtraX/ResourceManager.h>
#include <ExtraX/Singleton.h>

namespace ExtraX::Graphics::Base
{
	class ShaderBase
	{
	public:
		virtual void Apply() = 0;
	};

	template<GRAPHICS_LIB> 
	class ShaderResourceManager;

	template<GRAPHICS_LIB>
	class Shader;
}
#endif // !EXTRAX_SHADER_BASE_H
