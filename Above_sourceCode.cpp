// ABove beta source code

// Tells compiler to pack only essential files
#define WIN32_LEAN_AND_MEAN

#include <windows.h> // Used to communicate with Windows API.
#include <fstream>   // Used for config file.
#include <iostream>
#include <string>

using namespace std;

#define MY_HOT_KEY 1

bool configFileExist(string fileName){
    ifstream configFile(fileName);
    return configFile.good();
}

void addToStartup(){
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    
    string command = "reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\" /v MyProgram /t REG_SZ /d \"" +  string(exePath) + "\" /f";
    
    int result = system(command.c_str());
    
    if (result == 0) {
        MessageBoxA(NULL,"ABove was added to Startup.\n\nTo disable, Go to Task manager > startup Apps > ABove > disable.\n\nThank you for using the Software.", "ABove.exe", MB_OK | MB_ICONINFORMATION);
        return;
    } else {
        cerr << "Failed to add to startup!" << endl;
        return;
    }
    
}

void checkAndAddInStartup(){

    string fileName = "config.txt";
    string startUpConfig = "";

    if(configFileExist(fileName)){
        ifstream configFile(fileName);
        getline(configFile, startUpConfig);
        configFile.close();

        if(startUpConfig == "0" || startUpConfig == ""){
            addToStartup();  //Adds to startup

            ofstream configFileWrite(fileName);
            configFileWrite << "1" << endl;
            configFileWrite.close();
        }else{
            return;
        }
    }else{
        addToStartup();  //Adds to startup

        ofstream configFileWrite(fileName);
        configFileWrite << "1" << endl;
        configFileWrite.close();        
    }

    return;
}

//Entry point for Win32 API
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow){

    checkAndAddInStartup(); //Checks if the program was added to startup once, if not it adds it to startup.

    // Main logic Code

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
