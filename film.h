#ifndef FILM_H_INCLUDED
#define FILM_H_INCLUDED

#include <string>
#include "menu.h"

struct infoFilm
{
    std::string title;
    int year;
};

typedef struct Film *a_film;

struct Film
{
    infoFilm info;
    a_film next;
    a_film prev;
};


//Double-Linked List
struct ListFilm
{
    a_film first;
    a_film last;
};

ListFilm CreateListFilm();
a_film CreateFilm(std::string name, int year);
void DeallocateFilm(a_film &a);
a_film FindFilmByTitle(ListFilm L, std::string name);

void InsertFilm(ListFilm &L, a_film a);
void DeleteFilm(ListFilm &L, a_film a);

std::vector<a_film> GetAllFilmAddress(ListFilm L);

#endif // FILM_H_INCLUDED
