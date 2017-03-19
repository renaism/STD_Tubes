#include "actor.h"

ListActor CreateListActor()
{
    ListActor L;
    L.first = NULL;

    return L;
}

a_actor CreateActor(std::string name)
{
    a_actor a = new Actor;
    a->info.name = name;
    a->next = NULL;

    return a;
}

void DeallocateActor(a_actor &a)
{
    delete a;
    a = NULL;
}

a_actor FindLastActor(ListActor L)
{
    if(L.first != NULL)
    {
        a_actor last = L.first;
        while(last->next != L.first)
        {
            last = last->next;
        }

        return last;
    }
    else
    {
        return NULL;
    }
}

a_actor FindActorByName(ListActor L, std::string nameSearch)
{
    if(L.first != NULL)
    {
        for (char &c: nameSearch) c = std::toupper(c);
        a_actor a = L.first;
        do
        {
            std::string name = a->info.name;
            for (char &c: name) c = std::toupper(c);
            if(nameSearch == name)
            {
                return a;
            }
            else
            {
                a = a->next;
            }
        } while(a != L.first);
    }
    return NULL;
}

void InsertActor(ListActor &L, a_actor a)
{
    /*
        F.S : List of actors sorted alphabetically
    */
    if(L.first == NULL)
    {
        L.first = a;
        a->next = L.first;
    }
    else
    {
        std::string aName = a->info.name;
        std::string bName = "";
        for (char &c: aName) c = std::toupper(c);
        a_actor b = NULL;
        a_actor bPrev = NULL;
        do
        {
            if(b == NULL)
            {
                b = L.first;
                bPrev = L.first;
            }
            else
            {
                b = b->next;
            }
            bName = b->info.name;
            for (char &c: bName) c = std::toupper(c);
            if(aName > bName)
            {
                bPrev = b;
            }
        } while ((aName > bName) && (b->next != L.first));
        if ((b == L.first) && (aName < bName))
        {
            a->next = bPrev;
            FindLastActor(L)->next = a;
            L.first = a;

        }
        else
        {
            a->next = bPrev->next;
            bPrev->next = a;
        }
    }
}
void DeleteActor(ListActor &L, a_actor a)
{
    /*
        I.S : 'a' must be an address of an element in list 'L'
    */
    if(L.first == a)
    {
        if(L.first->next == L.first)
        {
            L.first = NULL;
        }
        else
        {
            FindLastActor(L)->next = a->next;
            L.first = a->next;
        }
    }
    else
    {
        //Find previous address in List
        a_actor prev = L.first;
        while((prev->next != a) && (prev->next != L.first))
        {
            prev = prev->next;
        }
        if(prev->next == a)
        {
            prev->next = a->next;
        }
    }
    a->next = NULL;
}

std::vector<a_actor> GetAllActorAddress(ListActor L)
{
    std::vector<a_actor> aT;
    if(L.first != NULL)
    {
        a_actor a = L.first;
        do
        {
            aT.push_back(a);
            a = a->next;
        } while(a != L.first);
    }

    return aT;
}

std::vector<a_actor> GetAllActorWithStr(ListActor L, std::string str)
{
    std::vector<a_actor> aT;
    if(L.first != NULL)
    {
        for(char &c: str) c = std::toupper(c);
        a_actor a = L.first;
        do
        {
            std::string name = a->info.name;
            for(char &c: name) c = std::toupper(c);
            if(name.find(str) != std::string::npos)
            {
                aT.push_back(a);
            }
            a = a->next;
        } while(a != L.first);
    }

    return aT;
}
