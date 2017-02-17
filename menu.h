#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER '\r'

typedef std::vector<std::string> menuOptions;

struct Menu
{
    std::string title;
    menuOptions options;
};

Menu GenerateMenu(std::string title, menuOptions options);
void ShowMenu(Menu M, int &sel);



#endif // MENU_H_INCLUDED
