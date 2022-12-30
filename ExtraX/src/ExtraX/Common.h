#pragma once
#ifndef EXTRAX_COMMON_H
#define EXTRAX_COMMON_H


#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#endif // _WIN32

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <type_traits>
#include <memory>
#include <bitset>
#include <array>
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace ExtraX
{
	enum class WINDOW_LIB
	{
		Win32,
		GLFW,
	};

	enum class GRAPHICS_LIB
	{
		DirectX11,
		DirectX12,
		OpenGL,
		Vulkan,
	};

	enum class MATHEMATICS_LIB
	{
		GLM,
	};

	enum class GUI_LIB
	{
		IMGUI,
	};
}



#ifdef _WIN32
	#define XX_DEBUGBREAK() __debugbreak()
#endif // _WIN32

#define XX_EXPAND_MACRO(x) x
#define XX_STRINGIFY_MACRO(x) #x



#ifdef USE_EXTRAX_SETTINGS
#include <ExtraXSettings.h>
#else
#include <ExtraX/DefaultSettings.h>
#endif // EXTRAX_SETTINGS





#endif // !EXTRAX_COMMON_H
