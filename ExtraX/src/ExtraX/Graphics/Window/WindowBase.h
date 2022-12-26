#pragma once
#ifndef EXTRAX_WINDOW_BASE_H
#define EXTRAX_WINDOW_BASE_H

#include <ExtraX/Common.h>
#include <ExtraX/Input.h>

namespace ExtraX::Graphics::Base
{
	constexpr int WINDOW_WIDTH = 800;

	constexpr int WINDOW_HEIGHT = 600;

	constexpr int TITLE_MAX = 128;

	const char* DEFAULT_TITLE = "ExtraX";

	class WindowBase
	{
	public:
		virtual bool ShouldClose() = 0;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual int GetPositionX() = 0;
		virtual int GetPositionY() = 0;
		virtual void SetTitle(const char* title) = 0;
		virtual void SetSize(int width, int height) = 0;
		virtual void SetPosition(int x, int y) = 0;
	};

	template<PLATFORM, GRAPHICS_API>
	class Window;
}



#endif // !EXTRAX_SIMPLE_WINDOW_BASE_H
