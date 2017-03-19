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

void DeallocateRelation(a_relation &a)
{
    delete a;
    a = NULL;
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
}

std::vector<a_relation> GetAllRelationAddress(ListRelation L)
{
    std::vector<a_relation> aT;
    if(L.first != NULL)
    {
        a_relation a = L.first;
        while(a != NULL)
        {
            aT.push_back(a);
            a = a->next;
        }
    }

    return aT;
}

std::vector<a_relation> GetAllRelationWithActor(ListRelation L, a_actor aA)
{
    std::vector<a_relation> relations;
    if(L.first != NULL && aA != NULL)
    {
        a_relation aR = L.first;
        while(aR != NULL)
        {
            if(aR->info.r_actor == aA)
            {
                relations.push_back(aR);
            }
            aR = aR->next;
        }
    }

    return relations;
}

std::vector<a_relation> GetAllRelationWithFilm(ListRelation L, a_film aF)
{
    std::vector<a_relation> relations;
    if(L.first != NULL && aF != NULL)
    {
        a_relation aR = L.first;
        while(aR != NULL)
        {
            if(aR->info.r_film == aF)
            {
                relations.push_back(aR);
            }
            aR = aR->next;
        }
    }

    return relations;
}

int TotalRelationOfActor(ListRelation L, a_actor aA)
{
    int n = 0;
    a_relation aR = L.first;
    while(aR != NULL)
    {
        if(aR->info.r_actor == aA)
        {
            n++;
        }
        aR = aR->next;
    }

    return n;
}

int TotalRelationOfFilm(ListRelation L, a_film aF)
{
    int n = 0;
    a_relation aR = L.first;
    while(aR != NULL)
    {
        if(aR->info.r_film == aF)
        {
            n++;
        }
        aR = aR->next;
    }

    return n;
}

void DeleteAllRelationWithActor(ListRelation &L, a_actor aA)
{
    std::vector<a_relation> relations = GetAllRelationWithActor(L, aA);
    for(a_relation &a: relations)
    {
        DeleteRelation(L, a);
        DeallocateRelation(a);
    }
}

void DeleteAllRelationWithFilm(ListRelation &L, a_film aF)
{
    std::vector<a_relation> relations = GetAllRelationWithFilm(L, aF);
    for(a_relation &a: relations)
    {
        DeleteRelation(L, a);
        DeallocateRelation(a);
    }
}

void ShowAllRelation(ListRelation L, bool selectable)
{
    if(L.first != NULL)
    {
        a_relation a = L.first;
        int i = 1;
        std::vector<std::string> opT;
        while(a != NULL)
        {
            std::string str = std::to_string(i) + ". " +
                        (a->info.r_actor)->info.name + " as " +
                        a->info.role + " in " +
                        (a->info.r_film)->info.title +
                        " (" + std::to_string((a->info.r_film)->info.year) + ")";
            opT.push_back(str);
            a = a->next;
            i++;
        }
        Menu M = GenerateMenu("All Relations", opT);
        int sel = 0;
        ShowMenu(M, sel);
    }
    else
    {
        Cell("Data of relations is empty!", 50, "left", true, true, true, true);
    }
}


