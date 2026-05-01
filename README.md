# Iwingui
A lightweight C++ header for building native Windows UIs without the usual Win32 hassle.

# how to setup
you only need to link the header
```C++
#include "Iwingui.h"
```
and to link the normail libraries for win32 gui
```lib
gdi32
user32
kernel32
comctl32
```
no need to add anything else
# how to use
first you will need to make this function
```
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
```
this function is like int main but for the win32 gui

exsample code looks like this

```C++
//this is like int main in normal C++
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    Appdata app;
    app.hInstance = hInstance;
    app.nCmdShow = nCmdShow;

    MakeApp(app);
    return 0;
}
```
that creates an empty window
"Appdata app;" makes a variable with the structure of AppData
Appdata is defined in the header

then it gives hInstance variable in the app variable the value of hInstance
hInstance was defined from win32 gui

then nCmdShow(in app variable) takes the value of nCmdShow from win32gui

then it runs the function MakeApp and gives it the app variable

the function does the rest
