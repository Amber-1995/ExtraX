#pragma once
#pragma once
#ifndef EXTRAX_WINDOW_H
#define EXTRAX_WINDOW_H


#include <ExtraX/Graphics/Window/Win32Window.h>
#include <ExtraX/Graphics/Window/GLFWWindow.h>

namespace ExtraX::Graphics
{
	using Window = Base::Window<DEFAULT_PALTFORM,DEFAULT_GRAPHICS_API>;
}

#endif // !EXTRAX_WINDOW_H

