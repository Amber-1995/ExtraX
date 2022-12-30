#pragma once
#ifndef EXTRAX_DEFAULT_SETTINGS_H
#define EXTRAX_DEFAULT_SETTINGS_H



namespace ExtraX
{
	using DEFAULT_COLOR_SCALAR_TYPE = float;
	using DEFAULT_MATRIX_SCALAR_TYPE = float;
	using DEFAULT_QUATERNION_SCALAR_TYPE = float;
	using DEFAULT_VECTOR_SCALAR_TYPE = float;

	constexpr WINDOW_LIB DEFAULT_WINDOW_LIB = WINDOW_LIB::GLFW;
	constexpr GRAPHICS_LIB DEFAULT_GRAPHICS_LIB = GRAPHICS_LIB::OpenGL;
	constexpr MATHEMATICS_LIB DEFAULT_MATHEMATICS_LIB = MATHEMATICS_LIB::GLM;
	constexpr GUI_LIB DEFAULT_GUI_LIB = GUI_LIB::IMGUI;
}






#endif // !EXTRAX_DEFAULT_SETTINGS_H
