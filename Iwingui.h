#ifndef IWINGUI_H_INCLUDED
#define IWINGUI_H_INCLUDED

#include <windows.h>
#include <string>
#include <vector>

//i can't find the goals but i did more then needed
//make a function for a button [done]
//an onclick function [done]
//make code good enough to be a .h file or a .a [dpne]

using namespace std;

struct Appdata {
    int height = 100;
    int width = 100;
    int X = 100;
    int Y = 100;
    string name = "no name";
    string Class = "MyWindowClass";
    LPSTR lpCmdLine;
    HINSTANCE hInstance;
    int nCmdShow;
};

struct Buttondata {
    HWND hwnd;
    HINSTANCE hInstance;

    string Class = "BUTTON";
    string name = "DO NOT CLICK";//you will be confused if you forgot to put a name
    string onclick = "function";

    int x = 50;
    int y = 50;
    int width = 200;
    int height = 100;
    int id = 1;

    DWORD style = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON;
};

struct menuitemdata{
    HWND hwnd;

    string name = "stop using default names";

    vector<string> popnames = {"ahmad" , "hello?" , "just write somthing"};
    vector<int> popids = {3,4,5};//every number needs an id
    vector<UINT> poptype = {MF_STRING , MF_STRING /*MF_SEPARATOR*/ , MF_STRING};
};

struct onclickdata {
    HWND hwnd;
    UINT msg;
    WPARAM wParam;
    LPARAM lParam;
};

struct actiondata{
    int id = 0;
    void (*func)(HWND);
};

inline vector<actiondata> actionlist = {};

//std::array<Action, 5> actions = { ... };
////         ^^^^^^  ^             ^^^^^
////         type    size          initial values
//now since when was Action a type??

int loadUI(HWND hwnd, LPARAM lParam);



//LRESULT is a dumb int
LRESULT callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



//some say use "int makebutton(const Buttondata& data)"
//i will not out of spite
void makebutton(Buttondata data){
    CreateWindow (
            data.Class.c_str(),
            data.name.c_str(),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            data.x,
            data.y,
            data.width,
            data.height,
            data.hwnd,
            (HMENU)data.id,
            data.hInstance,
            NULL);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg){
        case(WM_CREATE):
            loadUI(hwnd,lParam);
            break;

        case(WM_COMMAND): {
            int id = LOWORD(wParam);
            int code = HIWORD(wParam);
            int size_action = actionlist.size();

            if (code == BN_CLICKED) {
                for (int i = 0; i < size_action; i++) {
                    if (actionlist[i].id == id) {
                        actionlist[i].func(hwnd);
                        break;
                    }
                }
            }
            break;
        }

        case(WM_DESTROY):
            PostQuitMessage(0);
            return 0;
        default:
            callback(hwnd, msg, wParam, lParam);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void MakeApp(Appdata app) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;//here we set up the var
    wc.hInstance = app.hInstance;
    wc.lpszClassName = app.Class.c_str();
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        app.Class.c_str(), app.name.c_str(),
        WS_OVERLAPPEDWINDOW,
        app.X, app.Y, app.width, app.height,
        nullptr, nullptr, app.hInstance, nullptr
    );
    ShowWindow(hwnd, app.nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void menuitem(menuitemdata data){
    if(GetMenu(data.hwnd) == NULL){
        HMENU hMenuBar = CreateMenu();
        SetMenu(data.hwnd, hMenuBar);
    }
    HMENU hMenuBar = GetMenu(data.hwnd);

    HMENU menu = CreatePopupMenu();

    for(int i = 0; i < data.popnames.size(); i++){
        //could use ?: as i use gnu but others might use a defrent compiler
        AppendMenu(
                   menu,
                   data.poptype[i],
                   data.popids[i] ? data.popids[i] : 0 ,
                   data.popnames[i].c_str()
                   );
    }

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)menu, data.name.c_str());
    DrawMenuBar(data.hwnd);
}

void menubar(HWND hwnd){
        // Build the menu bar
        HMENU hMenuBar = CreateMenu();
        SetMenu(hwnd, hMenuBar); // attach it after the fact
        //return hMenuBar;
}

/*
always put this at the end of your file
Action actions[] = {
    {1, onButton1},
    {2, onButton2},
    {3, onButton3}
};
int actionCount = sizeof(actions) / sizeof(actions[0]);
*/

#endif // IWINGUI_H_INCLUDED
