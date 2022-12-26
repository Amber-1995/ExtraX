
#include <ExtraX/Graphics/Window/GLFWWindow.h>
#include <ExtraX/Input.h>

using namespace ExtraX;
using namespace ExtraX::Graphics::Base;

int main()
{
	Window<PLATFORM::CrossPlatform,GRAPHICS_API::OpenGL> w;

	
	while (!w.ShouldClose())
	{
		if (Input::GetKeyDown(KeyCode::A))
		{
			w.SetSize(1280, 720);
		}

		Input::Update();
	}
	
}