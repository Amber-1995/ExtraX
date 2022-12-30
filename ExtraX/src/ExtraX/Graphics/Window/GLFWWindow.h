#pragma once
#ifndef EXTRAX_GLFW_WINDOW_H
#define EXTRAX_GLFW_WINDOW_H


#include <ExtraX/Graphics/Window/WindowBase.h>

namespace ExtraX::Graphics::Base
{
	template<>
	class Window<WINDOW_LIB::GLFW> : public WindowBase
	{
	private:
		GLFWwindow* _window;
	public:
		Window(int width = WINDOW_WIDTH,int height = WINDOW_HEIGHT,const char* title = DEFAULT_TITLE, GLFWmonitor * monitor = NULL, GLFWwindow* share = NULL)
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			

			_window = glfwCreateWindow(width, height, title, monitor, share);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowPos(_window, (mode->width - WINDOW_WIDTH) / 2, (mode->height - WINDOW_HEIGHT) / 2);

			/*auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
			{
				glViewport(0, 0, width, height);
			};
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);*/

			auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					Input::SetKeyState(key, KeyState::Down);
					break;
				case GLFW_RELEASE:
					Input::SetKeyState(key, KeyState::Up);
					break;
				}
			};
			glfwSetKeyCallback(_window, key_callback);
		}

		virtual ~Window()
		{
			glfwDestroyWindow(_window);
			glfwTerminate();
		}

		GLFWwindow* GetWindow()
		{
			return _window;
		}

		bool ShouldClose()
		{
			glfwPollEvents();
			return glfwWindowShouldClose(_window);

		}

		int GetWidth()
		{
			int w, h;
			glfwGetWindowSize(_window, &w, &h);
			return w;
		}

		int GetHeight()
		{
			int w, h;
			glfwGetWindowSize(_window, &w, &h);
			return h;
		}

		int GetPositionX()
		{
			int x, y;
			glfwGetWindowPos(_window, &x, &y);
			return x;
		}

		int GetPositionY()
		{
			int x, y;
			glfwGetWindowPos(_window, &x, &y);
			return y;
		}
		
		void SetTitle(const char* title)
		{
			glfwSetWindowTitle(_window, title);
		}

		void SetSize(int width, int height)
		{
			glfwSetWindowSize(_window, width, height);
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowPos(_window, (mode->width - width) / 2, (mode->height - height) / 2);
		}

		void SetPosition(int x, int y)
		{
			glfwSetWindowPos(_window, x, y);
		}

	};
}




#endif // !EXTRAX_GLFW_WINDOW_H
