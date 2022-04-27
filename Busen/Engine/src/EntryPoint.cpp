#include <windows.h>
#include <string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
            PostQuitMessage(0);
        }
        break;
    case WM_CHAR:
        short a = 0;
        (*(char*)&a) = wParam;
        SetWindowTextA(hwnd, (char*)&a);
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 480, 480,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}