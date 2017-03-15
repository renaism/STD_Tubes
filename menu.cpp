#include "menu.h"

void CursorSetPos(short x, short y)
{
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

COORD CursorGetPos()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return {-1, -1};
    }

    return csbi.dwCursorPosition;
}

Menu GenerateMenu(std::string title, const std::vector<std::string> &opT)
{
    Menu M;
    M.title = title;
    M.options = opT;
    M.opReturn = opT.size()-1;

    return M;
}

Menu ConfirmationDialogue(std::string info)
{
    Menu M;
    M.title = info;
    M.options = {"Yes", "No"};
    M.opReturn = M.options.size()-1;

    return M;
}

void ShowMenu(Menu M, int &sel, bool hasReturn)
{
    int key = 0;
    if(sel < 0 || sel > M.opReturn)
    {
        sel = 0;
    }

    system("cls");
    if(!M.title.empty())
    {
        Cell(M.title, 50, "centre", true, true, true, true, 3, 1);
    }
    COORD cursorStartPos = {7, CursorGetPos().Y+1};
    std::string opt = "";
    for(int i = 0; i <= M.opReturn; i++)
    {
        if(i != 0)
        {
            opt += '\n';
        }
        opt += "     " + std::to_string(i+1) + ". " + M.options[i];
    }
    Cell(opt, 50, "left", true, true, true, true, 3);
    std::cout << "    <UP>/<DOWN> : Navigate            <ENTER> : Select\n";
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
                sel = M.opReturn;
            }

        }
        else if(key == KEY_DOWN)
        {
            CursorSetPos(cursorStartPos.X, cursorStartPos.Y + sel);
            std::cout << " ";
            sel++;
            if(sel > M.opReturn)
            {
                sel = 0;
            }
        }
    } while(key != KEY_ENTER);
}

void ShowMessage(std::string info)
{
    Menu M;
    M.title = info;
    M.options = {"Ok"};
    M.opReturn = 0;
    int sel = 0;
    ShowMenu(M, sel);
}

void InputField(Menu M, std::string &input)
{
    input = "";
    int sel = 0;
    system("cls");
    if(!M.title.empty())
    {
        Cell(M.title, 50, "centre", true, true, true, true, 3, 1);
    }
    COORD cursorStartPos = {7, CursorGetPos().Y+2};
    std::string opt = "";
    for(int i = 0; i <= M.opReturn; i++)
    {
        opt += "   " + M.options[i] + ":\n";
        if(i < M.opReturn) opt += "\n\n";
    }
    Cell(opt, 50, "left", true, true, true, true, 3);
    std::cout << "    <ENTER> : Confirm Input\n";
    COORD cursorEndPos = CursorGetPos();

    for(int i = 0; i <= M.opReturn; i++)
    {
        CursorSetPos(cursorStartPos.X, cursorStartPos.Y + (i * 3));
        std::string str;
        std::getline(std::cin, str);
        input += str;
        if(i < M.opReturn) input += '\n';
    }
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

void Cell(std::string text, int width, align alg, bool borderT, bool borderB, bool borderR, bool borderL, int offsetX, int offsetY)
{
    for(int i = 0; i < offsetY; i++)
    {
        std::cout << '\n';
    }

    if(borderT)
    {
        for(int i = 0; i < offsetX; i++)
        {
            std::cout << ' ';
        }
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

    std::stringstream textStream(text);
    while(textStream.good())
    {
        for(int i = 0; i < offsetX; i++)
        {
            std::cout << ' ';
        }
        std::string txtLine;
        std::getline(textStream, txtLine, '\n');
        if(borderL)
        {
            DrawBorderHorizontal();
        }

        int length = txtLine.length();
        int used = 0;

        if(alg == "centre")
        {
            if(length <= width)
            {
                int x = (int) (width - length) / 2;
                for(int i = 0; i < x; i++)
                {
                    std::cout << ' ';
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
                    std::cout << ' ';
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
                    std::cout << '.';
                }
                else
                {
                    std::cout << txtLine[i];
                }
            }
            else
            {
                std::cout << ' ';
            }
        }

        if(borderR)
        {
            DrawBorderHorizontal();
        }
        std::cout << '\n';
    }

    if(borderB)
    {
        for(int i = 0; i < offsetX; i++)
        {
            std::cout << ' ';
        }
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
