// Above beta source code

// Tells compiler to pack only essential files
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#define MY_HOT_KEY 1


//Entry point for Win32 API
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow){

    if(!RegisterHotKey(NULL,MY_HOT_KEY,MOD_ALT,'T')){  //Register hot key for this program.
        return 1;
    }

    MSG msg = {0};          // intialize the message.

    while(GetMessage(&msg,NULL,0,0) != 0){          // Recieves Message (events) from windows.
        if(msg.message == WM_HOTKEY){               // Checks if message is a hotkey press
            if(msg.wParam == MY_HOT_KEY){           // Checks if it our Hotkey (eg - Alt + T).

                HWND targetWindow = GetForegroundWindow();          // Gets which window is at top i.e. which window to pin

                if(targetWindow){
                    
                    DWORD currentState = GetWindowLong(targetWindow, GWL_EXSTYLE);      // Gets current state of that window i.e. if it is pinned or not.

                    if(currentState & WS_EX_TOPMOST){                   //Check if it is pinned.
                        SetWindowPos(targetWindow,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
                    }
                    else{
                        SetWindowPos(targetWindow,HWND_TOPMOST,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
                    }
                }
            }
        }
    }

    UnregisterHotKey(NULL, MY_HOT_KEY);


    return 0;

}
