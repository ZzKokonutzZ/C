#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

static bool quit = false;

struct {
    int width;
    int height;
    uint32_t *pixels;
} frame = {0};

double scalar_length(double a, double b) {
    return sqrt((a*a+b*b));
}

static int graybase=0x010101;

LRESULT CALLBACK WindowProcessMessage(HWND, UINT, WPARAM, LPARAM);

static BITMAPINFO frame_bitmap_info;
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    const wchar_t window_class_name[] = L"My Window Class";
    static WNDCLASS window_class = { 0 };
    window_class.lpfnWndProc = WindowProcessMessage;
    window_class.hInstance = hInstance;
    window_class.lpszClassName = window_class_name;
    RegisterClass(&window_class);
    
    frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
    frame_bitmap_info.bmiHeader.biPlanes = 1;
    frame_bitmap_info.bmiHeader.biBitCount = 32;
    frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
    frame_device_context = CreateCompatibleDC(0);
    
    static HWND window_handle;
    window_handle = CreateWindow(window_class_name, L"Drawing Pixels", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 0, 0, 500, 500, NULL, NULL, hInstance, NULL);
    if(window_handle == NULL) { return -1; }
    
    while(!quit) {
        static MSG message = { 0 };
        while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) { DispatchMessage(&message); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// test 1 : Langton's ant
        // static unsigned int p = 0;
        // static bool init=true;
        // static int d = 0;
        // static int d_tab[4]={0,0,0,0};
        unsigned int frame_size = frame.width*frame.height;
        // static int last_p=0x000000;
        // if (init) {
        // p=frame_size/2;
        // d_tab[0]=frame.width;
        // d_tab[1]=frame_size-1;
        // d_tab[2]=frame_size-frame.width;
        // d_tab[3]=1;
        // init=false;
        // }

        // if (last_p==0x000000) {
        //     frame.pixels[p%frame_size]=0xFFFFFF;
        //     d=d+1;
        // }
        // else {
        //     frame.pixels[p%frame_size]=0x000000;
        //     d=d-1;
        // }

        // last_p=frame.pixels[(p+d_tab[d%4])%frame_size];
        // frame.pixels[(p+=d_tab[d%4])%frame_size] = 0x0088FF;

        // if (p>frame_size) p-=frame_size;

// test 2 : speed tests

        POINT cursor;
        GetCursorPos(&cursor);
        ScreenToClient(window_handle, &cursor);
        static double time=1;
        for (int x=0;x<frame.width;x+=1) {
            for (int y=0;y<frame.height;y+=1) {
                int falloff = 10;
                int size=100;
                int intensity=10;
                
                // int t=(int)min(255,255 *intensity* falloff/(max(scalar_length(x-cursor.x,y+cursor.y-frame.height)-size,0)+falloff));
                double sinus = sin(0.01 * 3.141592 * scalar_length(x-cursor.x,y+cursor.y-frame.height)-time);
                int t = (int)min(255, 255 * sinus * sinus);
                frame.pixels[x+y*frame.width]=t*graybase;
            }
        }
        time+=0.1;
        


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        InvalidateRect(window_handle, NULL, FALSE);
        UpdateWindow(window_handle);
    }
    
    return 0;
}


LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_QUIT:
        case WM_DESTROY: {
            quit = true;
        } break;
        
        case WM_PAINT: {
            static PAINTSTRUCT paint;
            static HDC device_context;
            device_context = BeginPaint(window_handle, &paint);
            BitBlt(device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   paint.rcPaint.right - paint.rcPaint.left, paint.rcPaint.bottom - paint.rcPaint.top,
                   frame_device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   SRCCOPY);
            EndPaint(window_handle, &paint);
        } break;
        
        case WM_SIZE: {
            frame_bitmap_info.bmiHeader.biWidth  = LOWORD(lParam);
            frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);
            
            if(frame_bitmap) DeleteObject(frame_bitmap);
            frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, (void**)&frame.pixels, 0, 0);
            SelectObject(frame_device_context, frame_bitmap);
            
            frame.width =  LOWORD(lParam);
            frame.height = HIWORD(lParam);
        } break;
        
        default: {
            return DefWindowProc(window_handle, message, wParam, lParam);
        }
    }
    return 0;
}