
#include <windows.h>
#include <Windowsx.h>
#include <iostream>
#include <vector>
#include <string>
#include "resource.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 400
#define WINDOW_TITLE "Calculator"

using namespace std;


LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

/*
    BUTTONS 0-9 = NUMBERS
    10 = Period
    11 = equal sign

*/
HWND buttons[16];

HWND inputBox;

int WinStatus = 1;

int WINAPI WinMain(HINSTANCE hProgramInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){
    HWND hwnd;
    MSG msg;
    WNDCLASSEX wc;
    LPCTSTR wdClsName = "BaseWindow";
            wc.cbSize               = sizeof(WNDCLASSEX);
            wc.lpszClassName        = wdClsName;
            wc.hInstance            = hProgramInstance;
            wc.lpfnWndProc          = WindowProcedure;
            wc.lpszMenuName         = MAKEINTRESOURCE(ID_FILE);
            wc.cbWndExtra           = 0;
            wc.cbClsExtra           = 0;
            wc.hIcon                = LoadIcon(NULL, IDI_WINLOGO);
            wc.hIconSm              = LoadIcon(NULL, IDI_WINLOGO);
            wc.hCursor              = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground        = (HBRUSH)COLOR_WINDOW;
            wc.style                = CS_DBLCLKS;

        if(!RegisterClassEx(&wc)){
            MessageBox(NULL,"Failed to register base window class.","WC_REGISTER_FAILED",MB_OK|MB_ICONERROR);
            cout << "failed to register base window class" << endl;
            return 1;
        }
        hwnd = CreateWindow(wdClsName,WINDOW_TITLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT,WINDOW_WIDTH,WINDOW_HEIGHT,NULL,NULL,hProgramInstance,NULL);

        if( hwnd == NULL ){
            MessageBox(NULL, "WINDOW CREATION FAILED", "failed to create main window handle", MB_OK|MB_ICONERROR);
            return -1;
        }



        while(WinStatus != 0){
            while(PeekMessage(&msg,hwnd,0,0,PM_REMOVE)){
                TranslateMessage(&msg);
                DispatchMessage(&msg);

            }


        }
    return msg.wParam;
}


LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){
    int xScale = 0;
    int yScale = 64;

    switch(msg){
        case WM_CREATE:

            inputBox = CreateWindow("EDIT",NULL, WS_VISIBLE| WS_CHILD | ES_READONLY | ES_CENTER|ES_NOHIDESEL,0,0,WINDOW_WIDTH, 64, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            if( inputBox == NULL ){
               MessageBox(hwnd, "CONTROL CREATION FAILED", "Failed to create input box", MB_OK|MB_ICONERROR);
                SendMessage(hwnd,WM_CLOSE,wParam,lParam);
               break;
            }

            for( int i=9;i >= 0; i--){ //Loop to create the number buttons
                if( i == 6 || i == 3 || i == 0 ){ //Increase y axis (up/down) to move numbers to next line
                    yScale += 64;
                    xScale = 0;
                }
                buttons[i] = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                std::to_string(i).c_str(),      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                xScale,         // x position
                yScale,         // y position
                64,        // Button width
                64,        // Button height
                hwnd,     // Parent window
                NULL,       // No menu.
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);      // Pointer not needed.

                if( buttons[i] == NULL ){ //if the current button failed to be created

                    MessageBox(NULL, "FAIL", "Failed to create a HWND for BUTTONs", MB_OK|MB_ICONERROR);
                    SendMessage(hwnd,WM_CLOSE,wParam,lParam);
                    break;
                }

                xScale += 64;

            }

            //Decimal Button
            buttons[10] = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                ".",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                64,         // x position
                256,         // y position
                64,        // Button width
                64,        // Button height
                hwnd,     // Parent window
                NULL,       // No menu.
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);      // Pointer not needed.

            // EQUALS Button
            buttons[11] = CreateWindow(
                    "BUTTON",  // Predefined class; Unicode assumed
                    "=",      // Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                    128,         // x position
                    256,         // y position
                    64,        // Button width
                    64,        // Button height
                    hwnd,     // Parent window
                    NULL,       // No menu.
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.

            // PLUS sign button
            buttons[12] = CreateWindow(
                    "BUTTON",  // Predefined class; Unicode assumed
                    "+",      // Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                    192,         // x position
                    256,         // y position
                    64,        // Button width
                    64,        // Button height
                    hwnd,     // Parent window
                    NULL,       // No menu.
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.

            // MINUS sign button
            buttons[13] = CreateWindow(
                    "BUTTON",  // Predefined class; Unicode assumed
                    "-",      // Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                    192,         // x position
                    192,         // y position
                    64,        // Button width
                    64,        // Button height
                    hwnd,     // Parent window
                    NULL,       // No menu.
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.

            // MULTIPLY sign button
            buttons[14] = CreateWindow(
                    "BUTTON",  // Predefined class; Unicode assumed
                    "x",      // Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                    192,         // x position
                    128,         // y position
                    64,        // Button width
                    64,        // Button height
                    hwnd,     // Parent window
                    NULL,       // No menu.
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.

            // DIVISION sign button
           buttons[15] = CreateWindow(
                    "BUTTON",  // Predefined class; Unicode assumed
                    "÷",      // Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                    192,         // x position
                    64,         // y position
                    64,        // Button width
                    64,        // Button height
                    hwnd,     // Parent window
                    NULL,       // No menu.
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.

        break;

        case WM_KEYDOWN:
            switch(wParam){
                case VK_ESCAPE:
                    SendMessage(hwnd,WM_CLOSE,wParam,lParam);
                break;
            }
        break;




        case WM_DESTROY:
            WinStatus=0;
            PostQuitMessage(WM_QUIT);
        break;

        case WM_CLOSE:
                DestroyWindow(hwnd);
        break;

        default:
             return DefWindowProc(hwnd,msg,wParam,lParam);

    }
    return 0;

}
