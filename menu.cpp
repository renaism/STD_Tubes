#include "menu.h"

void CursorSetPos(int x, int y)
{
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

COORD CursorGetPos()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ), &csbi))
        return {-1. -1};
    return csbi.dwCursorPosition;
}

Menu GenerateMenu(std::string title, menuOptions options)
{
    Menu M;
    M.title = title;
    M.options = options;

    return M;
}

void ShowMenu(Menu M, int &sel)
{
    int key = 0;
    int length = M.options.size();
    sel = 0;
    COORD cursorStartPos;

    system("cls");
    Cell(M.title, 50, "centre", true, true, true, true);
    DrawBorderTopLeft();
    DrawBorderVertical(50);
    DrawBorderTopRight();
    std::cout << '\n';
    cursorStartPos = {4, CursorGetPos().Y};
    for(int i = 0; i < length; i++)
    {
        std::string opt = "";
        opt += "     ";
        opt += std::to_string(i+1) + ". " + M.options[i];
        Cell(opt, 50, "left", false, false, true, true);
    }
    DrawBorderBottomLeft();
    DrawBorderVertical(50);
    DrawBorderBottomRight();
    std::cout << '\n';
    COORD cursorEndPos = CursorGetPos();

    do
    {
        CursorSetPos(cursorStartPos.X, cursorStartPos.Y + sel);
        std::cout << ">";
        CursorSetPos(cursorEndPos.X, cursorEndPos.Y);
        key = getch();

        if(key == KEY_UP)
        {
            CursorSetPos(cursorStartPos.X, cursorStartPos.Y + sel);
            std::cout << " ";
            sel--;
            if(sel < 0)
            {
                sel = length-1;
            }

        }
        else if(key == KEY_DOWN)
        {
            CursorSetPos(cursorStartPos.X, cursorStartPos.Y + sel);
            std::cout << " ";
            sel++;
            if(sel > length-1)
            {
                sel = 0;
            }
        }
    } while(key != KEY_ENTER);
}

void DrawBorderVertical(int width)
{
    for(int i = 0; i < width; i++)
    {
        std::cout << "\304";
    }
}

void DrawBorderTopLeft()
{
    std::cout << "\332";
}

void DrawBorderTopRight()
{
    std::cout << "\277";
}

void DrawBorderBottomLeft()
{
    std::cout << "\300";
}

void DrawBorderBottomRight()
{
    std::cout << "\331";
}

void DrawBorderHorizontal()
{
    std::cout << "\263";
}

void Cell(std::string text, int width, align alg, bool borderT, bool borderB, bool borderR, bool borderL)
{
    if(borderT)
    {
        if(borderL)
        {
            DrawBorderTopLeft();
        }
        DrawBorderVertical(width);
        if(borderR)
        {
            DrawBorderTopRight();
        }
        std::cout << '\n';
    }
    if(borderL)
    {
        DrawBorderHorizontal();
    }

    int length = text.length();
    int used = 0;

    if(alg == "centre")
    {
        if(length <= width)
        {
            int x = (int) (width - length) / 2;
            for(int i = 0; i < x; i++)
            {
                std::cout << " ";
                used++;
            }
        }
    }

    else if(alg == "right")
    {
        if(length <= width)
        {
            int x = width - length;
            for(int i = 0; i < x; i++)
            {
                std::cout << " ";
                used++;
            }
        }
    }

    int x = width - used;
    for(int i = 0; i < x; i++)
    {
        if(i < length)
        {
            if((length > x) && (i > x-2))
            {
                std::cout << ".";
            }
            else
            {
                std::cout << text[i];
            }
        }
        else
        {
            std::cout << " ";
        }
    }

    if(borderR)
    {
        DrawBorderHorizontal();
    }
    std::cout << '\n';

    if(borderB)
    {
        if(borderL)
        {
            DrawBorderBottomLeft();
        }
        DrawBorderVertical(width);
        if(borderR)
        {
            DrawBorderBottomRight();
        }
        std::cout << '\n';
    }
}
