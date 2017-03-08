#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>
#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER '\r'

typedef std::vector<std::string> menuOptions;
typedef std::string align;

struct Menu
{
    std::string title;
    menuOptions options;
};

Menu GenerateMenu(std::string title, menuOptions options);
void ShowMenu(Menu M, int &sel);

void DrawBorderVertical(int width);
void DrawBorderTopLeft();
void DrawBorderTopRight();
void DrawBorderBottomLeft();
void DrawBorderBottomRight();
void DrawBorderHorizontal();

void Cell(std::string text, int width, align alg, bool borderT, bool borderB, bool borderR, bool borderL);

#endif // MENU_H_INCLUDED
