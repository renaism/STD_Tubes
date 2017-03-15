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
    a->info.title = name;
    a->info.year = year;
    a->next = NULL;
    a->prev = NULL;

    return a;
}

void DeallocateFilm(a_film &a)
{
    delete a;
    a = NULL;
}

a_film FindFilmByTitle(ListFilm L, std::string titleSearch)
{
    if(L.first != NULL)
    {
        for (char &c: titleSearch) c = std::toupper(c);
        a_film a = L.first;
        do
        {
            std::string title = a->info.title;
            for (char &c: title) c = std::toupper(c);
            if(titleSearch == title)
            {
                return a;
            }
            else
            {
                a = a->next;
            }
        } while(a != NULL);
    }
    return NULL;
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
}

std::vector<a_film> GetAllFilmAddress(ListFilm L)
{
    std::vector<a_film> aT;
    if(L.first != NULL)
    {
        a_film a = L.first;
        while (a != NULL)
        {
            aT.push_back(a);
            a = a->next;
        }
        return aT;
    }

    return aT;
}
