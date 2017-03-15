#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED

#include "menu.h"
#include "actor.h"
#include "film.h"

struct infoRelation
{
    a_actor r_actor;
    a_film r_film;
    std::string role;
};

typedef struct Relation *a_relation;

struct Relation
{
    infoRelation info;
    a_relation next;
    a_relation prev;
};

struct ListRelation
{
    a_relation first;
    a_relation last;
};

ListRelation CreateListRelation();
a_relation CreateRelation(a_actor r_a, a_film r_f, std::string role);
void DeallocateRelation(a_relation &a);

void InsertRelation(ListRelation &L, a_relation a);
void DeleteRelation(ListRelation &L, a_relation a);

std::vector<a_relation> GetAllRelationWithActor(ListRelation L, a_actor aA);
std::vector<a_relation> GetAllRelationWithFilm(ListRelation L, a_film aF);

void DeleteAllRelationWithActor(ListRelation &L, a_actor aA);
void DeleteAllRelationWithFilm(ListRelation &sL, a_film aF);

void ShowAllRelation(ListRelation L, bool selectable = false);

#endif // RELATION_H_INCLUDED
