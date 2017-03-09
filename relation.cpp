#include "relation.h"

ListRelation CreateListRelation()
{
    ListRelation L;
    L.first = NULL;
    L.last = NULL;

    return L;
}

a_relation CreateRelation(a_actor r_a, a_film r_f, std::string role)
{
    a_relation a = new Relation;
    a->info.r_actor = r_a;
    a->info.r_film = r_f;
    a->info.role = role;
    a->next = NULL;
    a->prev = NULL;

    return a;
}

void InsertRelation(ListRelation &L, a_relation a)
{
    if(L.first == NULL)
    {
        L.last = a;
    }
    else
    {
        a->next = L.first;
        L.first->prev = a;
    }
    L.first = a;
}

void DeleteRelation(ListRelation &L, a_relation a)
{
    if(a == L.first)
    {
        L.first = a->next;
    }
    else
    {
        (a->prev)->next = a->next;
    }

    if(a == L.last)
    {
        L.last = a->prev;
    }
    else
    {
        (a->next)->prev = a->prev;
    }

    a->next = NULL;
    a->prev = NULL;
    delete a;
}

void ShowAllRelation(ListRelation L)
{
    if(L.first != NULL)
    {
        a_relation a = L.first;
        int i = 1;
        while(a != NULL)
        {
            std::string str = std::to_string(i) + ". " +
                    (a->info.r_actor)->info.name + " as " +
                    a->info.role + " in " +
                    (a->info.r_film)->info.title +
                    " (" + std::to_string((a->info.r_film)->info.year) + ")";
            Cell(str, 100, "left", false, false, true, true);

            a = a->next;
            i++;
        }
    }
    else
    {
        Cell("Data of relations is empty!", 50, "left", true, true, true, true);
    }
}


