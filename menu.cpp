#include <conio.h>
#include <windows.h>

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
    do
    {
        system("cls");
        std::cout << M.title << " " << length << "\n\n";
        for(int i = 0; i < length; i++)
        {
            if(i == sel)
            {
                std::cout << "> ";
            }
            else
            {
                std::cout << "  ";
            }
            std::cout << i + 1 << ". " << M.options[i] << '\n';
        }

        key = getch();

        if(key == KEY_UP)
        {
            sel--;
            if(sel < 0)
            {
                sel = length-1;
            }
        }
        else if(key == KEY_DOWN)
        {
            sel++;
            if(sel > length-1)
            {
                sel = 0;
            }
        }

    } while(key != KEY_ENTER);
}
