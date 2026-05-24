<!-- <img width="324" height="324" alt="Copy of Iwingui (1)" src="https://github.com/user-attachments/assets/d3437819-8d1e-4507-9cdb-0211f554efa5" style="anchor:center" /> -->
<div align="center">
  <a><!-- i might have a website later so i will lave it just in case -->
    <picture><!-- i think we could make this code batter but not now-->
      <source media="(prefers-color-scheme: dark)" srcset="https://github.com/user-attachments/assets/d3437819-8d1e-4507-9cdb-0211f554efa5">
        <!-- i am unsure about this but it was in the next.js readme and they have a very good readme -->
      <img alt="Iwingui logo" src="https://github.com/user-attachments/assets/d3437819-8d1e-4507-9cdb-0211f554efa5" height="128">
    </picture>
  </a>
  <h1>Iwingui</h1>
</div>
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
or you could write this in the other linker settings if you want
```other linker settings
-lgdi32
-luser32
-lkernel32
-lcomctl32
```
no need to add anything else
# how to use
## making a window
first you will need to make this function
```C++
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
```
this function is like int main but for the win32 gui

exsample function:
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
that creates an empty window.
"Appdata app" makes a variable with the structure of AppData
Appdata is obviously defined inside the header

then it gives hInstance variable the value of hInstance
hInstance value was defined from the win32 gui

then nCmdShow(in app variable) takes the value of nCmdShow from win32gui

then it runs the function MakeApp and gives it the app variable

the function does the rest

## making a button
after using the WinMain function to make a window you can't use it more unless you run MakeApp(app); in a defrent thread
so *don't use it*
use the loadUI function

```C++
int loadUI(HWND hwnd,LPARAM lParam)
```
use the loadUI function to deal with loading the ui
exsample
```C++
void onButton1(HWND hwnd) {//onclick command
    MessageBox(hwnd, "Button 1 clicked", "Info", MB_OK);
}

void onButton2(HWND hwnd) {
    MessageBox(hwnd, "Button 2 clicked", "Info", MB_OK);
}

int loadUI(HWND hwnd,LPARAM lParam){
    menuitemdata data;
    data.hwnd = hwnd;
    menuitem(data);

    Buttondata button;
    //make sure to allways write the next 2 lines
    button.hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
    button.hwnd = hwnd;
    makebutton(button);

    //vector<actiondata>
    actionlist = {//the functions always have to be before naming them
        {1, onButton1},
        {2, onButton2}
    };

    return 1;
}
```
you have to gave name_you_choose.hwnd the value hwnd so it loads up for you
and also_name_you_choose.hInstance the value ((LPCREATESTRUCT)lParam)->hInstance;
and then you can call the function of what you want
menuitem is for making a menu, makebutton is for everything else

use actionlist when you want to gave a button an on click command

note:it is good to gave your buttons a name and you can give it a class if you want somthing else other then a button you can see how in the other examples

# other ui examples
```C++
void onButton1(HWND hwnd) {
    MessageBox(hwnd, "Button 1 clicked", "Info", MB_OK);
}

void onButton2(HWND hwnd) {
    MessageBox(hwnd, "Button 2 clicked", "Info", MB_OK);
}

int loadUI(HWND hwnd,LPARAM lParam){
    menuitemdata data;
    data.hwnd = hwnd;
    data.name = "the item name";
    data.popids = {1,2};
    data.popnames = {"hello" , "you can put any thing" , "this has no id" , "" , "but it still works"};
    data.poptype = {MF_STRING , MF_STRING , MF_STRING , MF_SEPARATOR , MF_STRING};
    //just add what you want to the menu
    menuitem(data);

    Buttondata button;
    button.hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
    button.hwnd = hwnd;
    button.Class = "BUTTON";
    button.height = 34;
    button.id = 3;
    button.name = "i can name this button!!";
    button.style = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON;
    button.width = 63;
    button.x = 45;
    button.y = 100;
    //just add what you want to the button
    makebutton(button);

    //vector<actiondata>
    actionlist = {//the functions always have to be before naming them
        {1, onButton1},
        {2, onButton2}
    };

    return 1;
}
```
