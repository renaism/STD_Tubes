#include <iostream>

#include "menu.h"
#include "menu.cpp"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    string title = "Main Menu";
    string opT[] = {"Insert", "Delete", "Exit"};
    menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
    Menu mainMenu = GenerateMenu(title, options);
    while(true)
    {
        int sel = 0;
        ShowMenu(mainMenu, sel);
        cout << "Menu selected: " << sel << endl;
        cin.get();
    }

    return 0;
}
