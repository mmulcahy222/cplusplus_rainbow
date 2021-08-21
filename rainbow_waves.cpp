#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <deque>
#include <vector>
#include <string.h>
#include <tchar.h>
#include <math.h>
using namespace std;
//global variables
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Rainbow Waves");

int width = 1000;
int height = 500;
float iteration = 0;
float vertical_wave_speed = 13;
int color_index = 0;
int line_count = 20;
int color_line_jitter = 5;
float distance_between_lines = .03;
int hue_variance = 3;
int horizontal_wave_distance = 30;

HINSTANCE hInst;
template <class T>
void print(T object)
{
    cout << object << endl;
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
COLORREF rgb_move_closer(int[] , int[] , int );
COLORREF rainbow_generator(int);
void DrawLines(HDC,RECT*, deque<vector<vector<float>>>);

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
                    _T("Call to RegisterClassEx failed!"),
                    _T("Windows Desktop Guided Tour"),
                    0);
        return 1;
    }
    hInst = hInstance;
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (!hWnd)
    {
        MessageBox(NULL,
                    _T("Call to CreateWindow failed!"),
                    _T("Rainbow Waves"),
                    0);
        return 1;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    const int ID_TIMER = 1;
    bool ret = SetTimer(hWnd, ID_TIMER, 50, NULL);
    if (ret == 0)
        MessageBox(hWnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// COLORREF rgb_move_closer(int original_colors[], int target_colors[], int step) 
// {
//     int count = 0;
//     int chunk;
//     int new_colors[3];
//     for(int counter = 0; counter < 2; counter++)
//     {
//         int original_color = original_colors[counter];
//         int target_color = target_colors[counter];
//         int difference = original_color - target_color;
//         chunk = (int)round(difference/steps);
//         new_colors[counter] = original_color - (chunk * step);
//         cout << new_colors[counter] << endl;
//         counter++;
//     }
//     return RGB(new_colors[0],new_colors[1],new_colors[2]);
// }

COLORREF rainbow_generator(int index)
{
    //index must be 0 to 255
    int red;
    int grn;
    int blu;
    int region = (int)floor((index / 255.0) * 6);
    int chunk = (int)((floor(index % 43) / 43) * 255);
    switch (region)
    {
    case 0:
        red = 255;
        grn = chunk;
        blu = 0;
        break; //red
    case 1:
        red = 255 - chunk;
        grn = 255;
        blu = 0;
        break; //yellow
    case 2:
        red = 0;
        grn = 255;
        blu = chunk;
        break; //green
    case 3:
        red = 0;
        grn = 255 - chunk;
        blu = 255;
        break; //cyan
    case 4:
        red = chunk;
        grn = 0;
        blu = 255;
        break; //blue
    case 5:
        red = 255;
        grn = 0;
        blu = 255 - chunk;
        break; //magenta
    }
    return RGB(red, grn, blu);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_COMMAND:
    {
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return 0;
        break;
    }
    case WM_TIMER:
    {
        RECT rect;
        HDC hdc = GetDC(hWnd);
        GetClientRect(hWnd,&rect);
        //background color
        HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));
        // FillRect(hdc, &rect, hBrush);
        //change color
        //Allows the pen color to change
        // SelectObject(hdc, GetStockObject(DC_PEN));
        //actually choose the pen color to change
        // SetDCPenColor(hdc, RGB(255, 255, 255));
        //end change color
        float separate_line_iteration;
        float y;
        int trailing_lines = 5;
        deque<vector<vector<float>>> coordinates_lines;
        separate_line_iteration = iteration/vertical_wave_speed;
        for (int i = 0; i < line_count; i++)
        {
            //WAS A HUGE BUG (SIZE WAS TOO MUCH)
            vector<vector<float>> coordinates_line;
            for (float x = 0; x < rect.right; x = x + 5)
            {
                // cos(x/30) is the horizontal difference between waves
                // (rect.bottom/2-50) is 
                // cos(seperate_line_iteration) IS THE AMPLITUDE
                y = rect.bottom / 2 + cos(x / horizontal_wave_distance) * (rect.bottom / 2 - 50) * cos(separate_line_iteration);
                //NO LINE SPANNING THE HORIZONTAL SCREN
                coordinates_line.push_back({x,y});
            }

            separate_line_iteration = separate_line_iteration - distance_between_lines;
            coordinates_lines.push_back(coordinates_line);
            if(coordinates_lines.size() > line_count)
            {
                auto line_to_destroy = coordinates_lines.front();
                coordinates_lines.pop_front();
                line_to_destroy.clear();
            }
        }
        DrawLines(hdc,&rect,coordinates_lines);
        iteration++;
        ReleaseDC(hWnd, hdc);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
}
return 0;
}


void DrawLines(HDC hdc, RECT *rect, deque<vector<vector<float>>> coordinates_lines)
{
    
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc,rect->right,rect->bottom);
    HGDIOBJ hbmOldBuffer = SelectObject(hdcBuffer, hbmBuffer);
    SelectObject(hdcBuffer, GetStockObject(DC_PEN));
    FillRect(hdcBuffer, rect, (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)));
    
    HPEN pen;
    float prell;
    COLORREF color;

    int line_index = 0;
    int line_color_index = 0;
    for (auto coordinates_line : coordinates_lines)
    {    
        for (auto coordinates : coordinates_line)
        {
            int x = (int)floor(coordinates[0]);
            int y = (int)floor(coordinates[1]);
            //remove the horizontal line, only show cosine waves
            if (x <= 0)
            {
                MoveToEx(hdcBuffer, x, y, 0);
                SelectObject(hdcBuffer, GetStockObject(DC_PEN));
                continue;
            }
            LineTo(hdcBuffer, x, (int)floor(y));
        }
        line_color_index = color_index + line_index;
        line_color_index = (line_color_index < 255) ? line_color_index : 0;
        SetDCPenColor(hdcBuffer, rainbow_generator(line_color_index));
        line_index += color_line_jitter;
    }
    color_index = color_index < 256 ? color_index + hue_variance : 0;
    BitBlt(hdc, 0, 0,rect->right,rect->bottom, hdcBuffer, 0, 0, SRCCOPY);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteDC(hdcBuffer);
    DeleteObject(hbmBuffer);
}