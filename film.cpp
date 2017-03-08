#include "film.h"

ListFilm CreateListFilm()
{
    ListFilm L;
    L.first = NULL;
    L.last = NULL;

    return L;
}

a_film CreateFilm(std::string name, int year)
{
    a_film a = new Film;
    a->info.name = name;
    a->info.year = year;
    a->next = NULL;
    a->prev = NULL;

    return a;
}

a_film FindFilmByName(ListFilm L, std::string name)
{
    if(L.first != NULL)
    {
        a_film a = L.first;
        while((a->info.name != name) && (a != L.last))
        {
            a = a->next;
        }
        if(a->info.name == name)
        {
            return a;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void InsertFilm(ListFilm &L, a_film a)
{
    /*
        F.S : New film inserted at the end of the list
    */
    if(L.last == NULL)
    {
        L.first = a;
        L.last = a;
    }
    else
    {
        a_film b = L.first;
        while(b != L.last)
        {
            b = b->next;
        }
        a->prev = b;
        b->next = a;
        L.last = a;
    }
}

void DeleteFilm(ListFilm &L, a_film a)
{
    if(a == L.first)
    {
        L.first = a->next;
    }
    else
    {
        a->prev->next = a->next;
    }

    if(a == L.last)
    {
        L.last = a->prev;
    }
    else
    {
        a->next->prev = a->prev;
    }

    a->next = NULL;
    a->prev = NULL;
    delete a;
}

void ShowAllFilm(ListFilm L)
{
    if(L.first != NULL)
    {
        DrawBorderTopLeft();
        DrawBorderVertical(50);
        DrawBorderTopRight();
        std::cout << '\n';
        a_film a = L.first;
        int i = 1;
        while(a != NULL)
        {
            std::string str = std::to_string(i) + ". " +
            a->info.name + " (" + std::to_string(a->info.year) + ")";
            Cell(str, 50, "left", false, false, true, true);

            a = a->next;
            i++;
        }
        DrawBorderBottomLeft();
        DrawBorderVertical(50);
        DrawBorderBottomRight();
        std::cout << '\n';
    }
    else
    {
        Cell("Data of films is empty!", 50, "left", true, true, true, true);
    }
}

