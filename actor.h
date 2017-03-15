#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#include <string>
#include "menu.h"

struct infoActor
{
    std::string name;
};

typedef struct Actor *a_actor;

struct Actor
{
    infoActor info;
    a_actor next;
};


//Circular Single-Linked List
struct ListActor
{
    a_actor first;
};

ListActor CreateListActor();
a_actor CreateActor(std::string name);
void DeallocateActor(a_actor &a);
a_actor FindLastActor(ListActor L);
a_actor FindActorByName(ListActor L, std::string nameSearch);

void InsertActor(ListActor &L, a_actor a);
void DeleteActor(ListActor &L, a_actor a);

std::vector<a_actor> GetAllActorAddress(ListActor L);

#endif // ACTOR_H_INCLUDED
