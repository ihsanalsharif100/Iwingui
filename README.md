# Iwingui
A lightweight C++ header for building native Windows UIs without the usual Win32 hassle.
this is an exsample for now
```C++
#include "Iwingui.h"

int loadUI(HWND hwnd,LPARAM lParam){
    menuitemdata data;
    data.hwnd = hwnd;
    menuitem(data);

    Buttondata button;
    //make sure to allways write the next 2 lines
    button.hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
    button.hwnd = hwnd;
    makebutton(button);
    return 1;
}

//this is like int main in normal C++
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    Appdata app;
    app.hInstance = hInstance;
    app.nCmdShow = nCmdShow;

    MakeApp(app);
    return 0;
}

void onButton1(HWND hwnd) {
    MessageBox(hwnd, "Button 1 clicked", "Info", MB_OK);
}

void onButton2(HWND hwnd) {
    MessageBox(hwnd, "Button 2 clicked", "Info", MB_OK);
}

Action actions[] = {
    {1, onButton1},
    {2, onButton2}
};
int actionCount = sizeof(actions) / sizeof(actions[0]);

```
