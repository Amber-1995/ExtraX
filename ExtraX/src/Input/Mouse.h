#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__



#include <windows.h>
#include <memory>
#include "../Data/Data.h"

namespace XX 
{

    // マウスモード
    typedef enum Mouse_PositionMode_tag
    {
        MOUSE_POSITION_MODE_ABSOLUTE, // 絶対座標モード
        MOUSE_POSITION_MODE_RELATIVE, // 相対座標モード
    } Mouse_PositionMode;


    //マウスボタン
    typedef enum Mouse_Button_tag
    {
        M_LETT_BUTTON,
        M_MIDDLE_BUTTON,
        M_RIGHT_BUTTON,
        M_X_BUTTON_1,
        M_X_BUTTON_2,
    }Mouse_Button;


    // マウス状態構造体
    typedef struct MouseState_tag
    {
        bool leftButton;
        bool middleButton;
        bool rightButton;
        bool xButton1;
        bool xButton2;
        int x;
        int y;
        int scrollWheelValue;
        Mouse_PositionMode positionMode;
    } Mouse_State;



    class Mouse
    {
    public:
        virtual ~Mouse(void);

        void Init(HWND window);

        void Update(void);

        XXVector2 GetMousePosition(void);
        bool GetMouseButton(Mouse_Button mouse_button);
        bool GetMouseButtonUp(Mouse_Button mouse_button);
        bool GetMouseButtonDown(Mouse_Button mouse_button);
        int GetScrollWheelValue(void);

        void ResetScrollWheelValue(void);
        void SetMode(Mouse_PositionMode mode);
        void SetVisible(bool visible);

        bool IsConnected(void);
        bool IsVisible(void);

    private:
        Mouse_State _current_state;
        Mouse_State _last_state;

        HWND               _window;
        Mouse_PositionMode _mode;
        HANDLE             _scroll_wheel_value;
        HANDLE             _relative_read;
        HANDLE             _absolute_mode;
        HANDLE             _relative_mode;
        int                _last_x;
        int                _last_y;
        int                _relative_x;
        int                _relative_y;
        bool               _in_focus;

        Mouse();
        Mouse(const Mouse& other) = delete;
        Mouse& operator=(const Mouse&) = delete;
        void ClipToWindow();

        void ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

        friend class Input;
    };

}

#endif // !__MOUSE_H__
