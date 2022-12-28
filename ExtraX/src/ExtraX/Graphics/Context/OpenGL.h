#pragma once
#ifndef EXTRAX_OPENGL_H
#define EXTRAX_OPENGL_H

#include <ExtraX/Graphics/Context/ContextBase.h>


namespace ExtraX::Graphics::Base
{

	class OpenGLContextBase : public ContextBase
	{
	public:
		virtual ~OpenGLContextBase() = default;

		void ClearColor(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
		}

		void Clear(unsigned int mask)
		{
			glClear(mask);
		}

		virtual void SwapBuffers() = 0;

	};

#ifdef _WIN32
	template<>
	class Context<PLATFORM::Windows, GRAPHICS_LIB::OpenGL> : public OpenGLContextBase
	{
	private:
		Window<PLATFORM::Windows, GRAPHICS_LIB::OpenGL>* _window;
		HDC _dc;
		HGLRC _rc;
	public:
		Context(Window<PLATFORM::Windows, GRAPHICS_LIB::OpenGL>* window = GetSingleton<Window<PLATFORM::Windows, GRAPHICS_LIB::OpenGL>>())
		{
			_window = window;
			_dc = GetDC(window->GetHandle());

			PIXELFORMATDESCRIPTOR pfd;
			ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 24;
			pfd.cStencilBits = 8;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

			int format = ChoosePixelFormat(_dc, &pfd);

			SetPixelFormat(_dc, format, &pfd);

			_rc = wglCreateContext(_dc);

			wglMakeCurrent(_dc, _rc);

			gladLoadGL();

			glViewport(0, 0, _window->GetWidth(), _window->GetHeight());
		}

		virtual ~Context()
		{

		}

		void SwapBuffers() override
		{
			::SwapBuffers(_dc);
		}

	};
#endif

	template<>
	class Context<PLATFORM::CrossPlatform, GRAPHICS_LIB::OpenGL> : public OpenGLContextBase
	{
	private:
		Window<PLATFORM::CrossPlatform, GRAPHICS_LIB::OpenGL>* _window;
	public:
		Context(Window<PLATFORM::CrossPlatform, GRAPHICS_LIB::OpenGL>* window = GetSingleton <Window<PLATFORM::CrossPlatform, GRAPHICS_LIB::OpenGL>>())
		{
			_window = window;
			glfwMakeContextCurrent(_window->GetWindow());
			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			glViewport(0, 0, _window->GetWidth(), _window->GetHeight());
		}

		virtual ~Context()
		{
			
		}

		void SwapBuffers() override
		{
			glfwSwapBuffers(_window->GetWindow());
		}
	};

}

#endif // !EXTRAX_OPENGL_H
