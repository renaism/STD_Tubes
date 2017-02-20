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
    int sel = 0;
    do
    {
        ShowMenu(mainMenu, sel);
    } while(sel != 2);
    cout << "Program exited." << endl;
    cin.get();

    return 0;
}
