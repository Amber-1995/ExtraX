#pragma once
#ifndef EXTRAX_CONTEXT_BASE_H
#define EXTRAX_CONTEXT_BASE_H

#include <ExtraX/Common.h>
#include <ExtraX/Graphics/Window.h>
#include <ExtraX/Singleton.h>

namespace ExtraX::Graphics::Base
{
	class ContextBase
	{
	public:
		virtual ~ContextBase() = default;
	};

	template<WINDOW_LIB,GRAPHICS_LIB>
	class Context;
}


#endif // !EXTRAX_CONTEXT_H
