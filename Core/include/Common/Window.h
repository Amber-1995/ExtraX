#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "ExtraX.h"

namespace XX
{
	class Window
	{
    private:
        uint32_t _width;
        uint32_t _height;
        std::string _title;


    public:
        Window(int width, int height, const std::string& title);
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        virtual ~Window();

        uint32_t GetWidth();

        uint32_t GetHeight();

        void SetSize(uint32_t width, uint32_t height);

        std::string GetTitle();

        void SetTitle(const std::string& title);

        void SetFullScreen(bool enalbe);
	};
}


#endif // !CORE_WINDOW_H

