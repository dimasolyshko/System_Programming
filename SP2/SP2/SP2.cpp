#include <Windows.h>

int age = 5;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Создание и настройка окна
    const wchar_t* className = L"SampleWindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"Регистрация класса окна не удалась", L"Ошибка", MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindow(className, L"Лабораторная работа", WS_OVERLAPPEDWINDOW, 100, 100, 400, 100, NULL, NULL, NULL, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Создание окна не удалось", L"Ошибка", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void CreatePopup(HWND hwnd, LPCWSTR text)
{
    MessageBox(hwnd, text, L"Всплывающее окно", MB_OK | MB_ICONINFORMATION);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Создаем поле для ввода текста
        HWND hEdit = CreateWindow(TEXT("edit"), L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 20, 23, 200, 20, hwnd, (HMENU)1, NULL, NULL);

        // Создаем кнопку
        CreateWindow(TEXT("button"), L"Показать текст", WS_VISIBLE | WS_CHILD, 230, 20, 120, 30, hwnd, (HMENU)2, NULL, NULL);
    }
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 2) // ID кнопки
        {
            // Получаем текст из поля ввода
            WCHAR buffer[256];
            GetDlgItemText(hwnd, 1, buffer, sizeof(buffer));

            // Отображаем текст во всплывающем окне
            CreatePopup(hwnd, buffer);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
