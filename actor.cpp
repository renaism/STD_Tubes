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

a_actor FindActorByName(ListActor L, std::string name)
{
    if(L.first != NULL)
    {
        a_actor a = L.first;
        while((a->info.name != name) && (a->next != L.first))
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
        //boost::algorithm::to_upper(aName);
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
            //boost::algorithm::to_upper(bName);
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
void DeleteActor(ListActor &L, a_actor &a)
{
    /*
        I.S : 'a' must be an address of an element in list 'L'
    */
    //Find previous address
    if(L.first == a)
    {
        L.first = a->next;
    }
    else
    {
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
    delete a;
}

void ShowAllActor(ListActor L)
{
    if(L.first != NULL)
    {
        DrawBorderTopLeft();
        DrawBorderVertical(50);
        DrawBorderTopRight();
        std::cout << '\n';
        a_actor a = L.first;
        int i = 1;
        do
        {
            std::string str = std::to_string(i) + ". " + a->info.name;
            Cell(str, 50, "left", false, false, true, true);

            a = a->next;
            i++;
        } while(a != L.first);
        DrawBorderBottomLeft();
        DrawBorderVertical(50);
        DrawBorderBottomRight();
        std::cout << '\n';
    }
    else
    {
        Cell("Data of actors is empty!", 50, "left", true, true, true, true);
    }
}
