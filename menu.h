#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>
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
    std::vector<std::string> options;
    int opReturn;
};

void CursorSetPos(short x, short y);
COORD CursorGetPos();

Menu GenerateMenu(std::string title, const std::vector<std::string> &opT);
Menu ConfirmationDialogue(std::string info);
void ShowMenu(Menu M, int &sel, bool hasReturn = true);
void ShowMessage(std::string info);
void InputField(Menu M, std::string &input);

void DrawBorderVertical(int width);
void DrawBorderTopLeft();
void DrawBorderTopRight();
void DrawBorderBottomLeft();
void DrawBorderBottomRight();
void DrawBorderHorizontal();

void Cell(std::string text, int width, align alg, bool borderT, bool borderB, bool borderR, bool borderL, int offsetX = 0, int offsetY = 0);

#endif // MENU_H_INCLUDED
