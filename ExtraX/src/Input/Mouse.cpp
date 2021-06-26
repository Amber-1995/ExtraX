

#include "Mouse.h"
#include <windowsx.h>
#include <assert.h>

namespace XX 
{

#define SAFE_CLOSEHANDLE(h) if(h){CloseHandle(h); h = NULL;}

    Mouse::Mouse() :
        _current_state(),
        _last_state(),
        _window(nullptr),
        _mode(MOUSE_POSITION_MODE_ABSOLUTE),
        _scroll_wheel_value(nullptr),
        _relative_read(nullptr),
        _absolute_mode(nullptr),
        _relative_mode(nullptr),
        _last_x(0),
        _last_y(0),
        _relative_x(INT32_MAX),
        _relative_y(INT32_MAX),
        _in_focus(true)
    {
       
    }

    Mouse::~Mouse(void)
    {
        SAFE_CLOSEHANDLE(_scroll_wheel_value);
        SAFE_CLOSEHANDLE(_relative_read);
        SAFE_CLOSEHANDLE(_absolute_mode);
        SAFE_CLOSEHANDLE(_relative_mode);
    }

    void Mouse::Init(HWND window)
    {
        _window = window;
        RAWINPUTDEVICE Rid;
        Rid.usUsagePage = 0x01 /* HID_USAGE_PAGE_GENERIC */;
        Rid.usUsage = 0x02     /* HID_USAGE_GENERIC_MOUSE */;
        Rid.dwFlags = RIDEV_INPUTSINK;
        Rid.hwndTarget = _window;
        RegisterRawInputDevices(&Rid, 1, sizeof(RAWINPUTDEVICE));

        if (!_scroll_wheel_value) { _scroll_wheel_value = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_MODIFY_STATE | SYNCHRONIZE); }
        if (!_relative_read) { _relative_read = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_MODIFY_STATE | SYNCHRONIZE); }
        if (!_absolute_mode) { _absolute_mode = CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE); }
        if (!_relative_mode) { _relative_mode = CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE); }
    }

    void Mouse::Update(void)
    {
        _last_state = _current_state;
    }

    XXVector2 Mouse::GetMousePosition(void)
    {
        if (_mode == MOUSE_POSITION_MODE_RELATIVE) {

            DWORD result = WaitForSingleObjectEx(_relative_read, 0, FALSE);
            if (result == WAIT_FAILED) {
				return XXVector2((float)_current_state.x, (float)_current_state.y);
            }

            if (result == WAIT_OBJECT_0) {
                return XXVector2(0.0f, 0.0f);
            }
            else {
                SetEvent(_relative_read);
            }
        }
		return XXVector2((float)_current_state.x, (float)_current_state.y);
    }

    bool Mouse::GetMouseButton(Mouse_Button mouse_button)
    {
        switch (mouse_button)
        {
        case M_LETT_BUTTON:
            return _current_state.leftButton;
            break;
        case M_MIDDLE_BUTTON:
            return _current_state.middleButton;
            break;
        case M_RIGHT_BUTTON:
            return _current_state.rightButton;
            break;
        case M_X_BUTTON_1:
            return _current_state.xButton1;
            break;
        case M_X_BUTTON_2:
            return _current_state.xButton2;
            break;
        }
        return false;
    }

    bool Mouse::GetMouseButtonUp(Mouse_Button mouse_button)
    {
        switch (mouse_button)
        {
        case M_LETT_BUTTON:
            return (!_current_state.leftButton) && _last_state.leftButton;
            break;
        case M_MIDDLE_BUTTON:
            return (!_current_state.middleButton) && _last_state.middleButton;
            break;
        case M_RIGHT_BUTTON:
            return (!_current_state.rightButton) && _last_state.rightButton;
            break;
        case M_X_BUTTON_1:
            return (!_current_state.xButton1) && _last_state.xButton1;
            break;
        case M_X_BUTTON_2:
            return (!_current_state.xButton2) && _last_state.xButton2;
            break;
        }
        return false;
    }

    bool Mouse::GetMouseButtonDown(Mouse_Button mouse_button)
    {
        switch (mouse_button)
        {
        case M_LETT_BUTTON:
            return _current_state.leftButton && (!_last_state.leftButton);
            break;
        case M_MIDDLE_BUTTON:
            return _current_state.middleButton && (!_last_state.middleButton);
            break;
        case M_RIGHT_BUTTON:
            return _current_state.rightButton && (!_last_state.rightButton);
            break;
        case M_X_BUTTON_1:
            return _current_state.xButton1 && (!_last_state.xButton1);
            break;
        case M_X_BUTTON_2:
            return _current_state.xButton2 && (!_last_state.xButton2);
            break;
        }
        return false;
    }
    int Mouse::GetScrollWheelValue(void)
    {
        DWORD result = WaitForSingleObjectEx(_scroll_wheel_value, 0, FALSE);
        if (result == WAIT_FAILED) {
            return _current_state.scrollWheelValue;
        }

        if (result == WAIT_OBJECT_0) {

            return 0;
        }

		return _current_state.scrollWheelValue;
    }

    void Mouse::ResetScrollWheelValue(void)
    {
        SetEvent(_scroll_wheel_value);
    }
    void Mouse::SetMode(Mouse_PositionMode mode)
    {
        if (_mode == mode)
            return;

        SetEvent((mode == MOUSE_POSITION_MODE_ABSOLUTE) ? _absolute_mode : _relative_mode);

        assert(_window != NULL);

        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_HOVER;
        tme.hwndTrack = _window;
        tme.dwHoverTime = 1;
        TrackMouseEvent(&tme);
    }
    void Mouse::SetVisible(bool visible)
    {
        if (_mode == MOUSE_POSITION_MODE_RELATIVE) {
            return;
        }

        CURSORINFO info = { sizeof(CURSORINFO), 0, nullptr, {} };
        GetCursorInfo(&info);

        bool isVisible = (info.flags & CURSOR_SHOWING) != 0;

        if (isVisible != visible) {
            ShowCursor(visible);
        }
    }

    bool Mouse::IsConnected(void)
    {
        return GetSystemMetrics(SM_MOUSEPRESENT) != 0;
    }
    bool Mouse::IsVisible(void)
    {

        if (_mode == MOUSE_POSITION_MODE_RELATIVE) {
            return false;
        }

        CURSORINFO info = { sizeof(CURSORINFO), 0, nullptr, {} };
        GetCursorInfo(&info);

        return (info.flags & CURSOR_SHOWING) != 0;
    }

    void Mouse::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        HANDLE evts[3] = {
           _scroll_wheel_value,
           _absolute_mode,
           _relative_mode
        };

        switch (WaitForMultipleObjectsEx(_countof(evts), evts, FALSE, 0, FALSE))
        {
        case WAIT_OBJECT_0:
            _current_state.scrollWheelValue = 0;
            ResetEvent(evts[0]);
            break;

        case (WAIT_OBJECT_0 + 1):
        {
            _mode = MOUSE_POSITION_MODE_ABSOLUTE;
            ClipCursor(nullptr);

            POINT point;
            point.x = _last_x;
            point.y = _last_y;

            // リモートディスクトップに対応するために移動前にカーソルを表示する
            ShowCursor(TRUE);

            if (MapWindowPoints(_window, nullptr, &point, 1)) {
                SetCursorPos(point.x, point.y);
            }

            _current_state.x = _last_x;
            _current_state.y = _last_y;
        }
        break;

        case (WAIT_OBJECT_0 + 2):
        {
            ResetEvent(_relative_read);

            _mode = MOUSE_POSITION_MODE_RELATIVE;
            _current_state.x = _current_state.y = 0;
            _relative_x = INT32_MAX;
            _relative_y = INT32_MAX;

            ShowCursor(FALSE);

            ClipToWindow();
        }
        break;

        case WAIT_FAILED:
            return;
        }

        switch (message)
        {
        case WM_ACTIVATEAPP:
            if (wParam) {

                _in_focus = true;

                if (_mode == MOUSE_POSITION_MODE_RELATIVE) {

                    _current_state.x = _current_state.y = 0;
                    ShowCursor(FALSE);
                    ClipToWindow();
                }
            }
            else {
                int scrollWheel = _current_state.scrollWheelValue;
                memset(&_current_state, 0, sizeof(_current_state));
                _current_state.scrollWheelValue = scrollWheel;
                _in_focus = false;
            }
            return;

        case WM_INPUT:
            if (_in_focus && _mode == MOUSE_POSITION_MODE_RELATIVE) {

                RAWINPUT raw;
                UINT rawSize = sizeof(raw);

                GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &raw, &rawSize, sizeof(RAWINPUTHEADER));

                if (raw.header.dwType == RIM_TYPEMOUSE) {

                    if (!(raw.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)) {

                        _current_state.x = raw.data.mouse.lLastX;
                        _current_state.y = raw.data.mouse.lLastY;

                        ResetEvent(_relative_read);
                    }
                    else if (raw.data.mouse.usFlags & MOUSE_VIRTUAL_DESKTOP) {

                        // リモートディスクトップなどに対応
                        const int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
                        const int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

                        int x = (int)((raw.data.mouse.lLastX / 65535.0f) * width);
                        int y = (int)((raw.data.mouse.lLastY / 65535.0f) * height);

                        if (_relative_x == INT32_MAX) {
                            _current_state.x = _current_state.y = 0;
                        }
                        else {
                            _current_state.x = x - _relative_x;
                            _current_state.y = y - _relative_y;
                        }

                        _relative_x = x;
                        _relative_y = y;

                        ResetEvent(_relative_read);
                    }
                }
            }
            return;


        case WM_MOUSEMOVE:
            break;

        case WM_LBUTTONDOWN:
            _current_state.leftButton = true;
            break;

        case WM_LBUTTONUP:
            _current_state.leftButton = false;
            break;

        case WM_RBUTTONDOWN:
            _current_state.rightButton = true;
            break;

        case WM_RBUTTONUP:
            _current_state.rightButton = false;
            break;

        case WM_MBUTTONDOWN:
            _current_state.middleButton = true;
            break;

        case WM_MBUTTONUP:
            _current_state.middleButton = false;
            break;

        case WM_MOUSEWHEEL:
            _current_state.scrollWheelValue += GET_WHEEL_DELTA_WPARAM(wParam);
            return;

        case WM_XBUTTONDOWN:
            switch (GET_XBUTTON_WPARAM(wParam))
            {
            case XBUTTON1:
                _current_state.xButton1 = true;
                break;

            case XBUTTON2:
                _current_state.xButton2 = true;
                break;
            }
            break;

        case WM_XBUTTONUP:
            switch (GET_XBUTTON_WPARAM(wParam))
            {
            case XBUTTON1:
                _current_state.xButton1 = false;
                break;

            case XBUTTON2:
                _current_state.xButton2 = false;
                break;
            }
            break;

        case WM_MOUSEHOVER:
            break;

        default:
            // マウスに対するメッセージは無かった…
            return;
        }

        if (_mode == MOUSE_POSITION_MODE_ABSOLUTE) {

            // すべてのマウスメッセージに対して新しい座標を取得する
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);

            _current_state.x = _last_x = xPos;
            _current_state.y = _last_y = yPos;
        }
    }

    void Mouse::ClipToWindow(void)
    {
        assert(_window != NULL);

        RECT rect;
        GetClientRect(_window, &rect);

        POINT ul;
        ul.x = rect.left;
        ul.y = rect.top;

        POINT lr;
        lr.x = rect.right;
        lr.y = rect.bottom;

        MapWindowPoints(_window, NULL, &ul, 1);
        MapWindowPoints(_window, NULL, &lr, 1);

        rect.left = ul.x;
        rect.top = ul.y;

        rect.right = lr.x;
        rect.bottom = lr.y;

        ClipCursor(&rect);
    }

}