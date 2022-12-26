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
#include <spdlog/spdlog.h>


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
	enum class PLATFORM
	{
		CrossPlatform,
		Windows,
		Linux,
	};

	enum class GRAPHICS_API
	{
		DirectX11,
		DirectX12,
		OpenGL,
		Vulkan,
	};
}


#ifdef EXTRAX_SETTINGS
#include <ExtraXSettings.h>
#else
#include <ExtraX/DefaultSettings.h>
#endif // EXTRAX_SETTINGS





#endif // !EXTRAX_COMMON_H
