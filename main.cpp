#include <iostream>
#include <sstream>

#include "menu.h"

#include "actor.h"
#include "film.h"
#include "relation.h"

using namespace std;

void EditActorDataMenu(ListActor &LA);
void EditFilmDataMenu(ListFilm &LF);
void DisplayDataMenu(ListActor LA, ListFilm LF, ListRelation LR);

void CreateNewActor(ListActor &LA);
void CreateNewFilm(ListFilm &LF);

int main()
{
    ListActor ListA = CreateListActor();
    ListFilm ListF = CreateListFilm();
    ListRelation ListR = CreateListRelation();

    string title = "Main Menu";
    string opT[] = {"Edit Actor Data", "Edit Film Data", "Display Data", "Exit"};
    int opSize = sizeof(opT) / sizeof(opT[0]);
    menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
    Menu mainMenu = GenerateMenu(title, options);
    int sel = 0;
    do
    {
        ShowMenu(mainMenu, sel);
        if(sel == 0)
        {
            EditActorDataMenu(ListA);
        }
        else if(sel == 1)
        {
            EditFilmDataMenu(ListF);
        }
        else if(sel == 2)
        {
            DisplayDataMenu(ListA, ListF, ListR);
        }
    } while(sel != opSize-1);
    cout << "Program exited." << endl;
    cin.get();



//    ShowAllActor(ListA);
//
//    cout << "Insert Aktor...\n";
//    cin.get();
//    InsertActor(ListA, CreateActor("Vladimir Putin"));
//    InsertActor(ListA, CreateActor("Nelson Mandela"));
//    InsertActor(ListA, CreateActor("Djadjang Nurjaman"));
//    InsertActor(ListA, CreateActor("Zinedine Zidane"));
//    InsertActor(ListA, CreateActor("Wafer Renyah"));
//    InsertActor(ListA, CreateActor("Hayao Miyazaki"));
//
//    ShowAllActor(ListA);
//    cout << endl;
//
//    ShowAllFilm(ListF);
//
//    cout << "Insert Pelem...\n";
//    cin.get();
//    InsertFilm(ListF, CreateFilm("Jalangkung", 2017));
//    InsertFilm(ListF, CreateFilm("Proklamasi", 1945));
//    InsertFilm(ListF, CreateFilm("Farras Shippuden", 1999));
//
//    ShowAllFilm(ListF);
//    cout << endl;
//
//    a_actor a;
//    a_film f;
//    a_relation r;
//
//    a = FindActorByName(ListA, "Wafer Renyah");
//    f = FindFilmByName(ListF, "Jalangkung");
//    r = CreateRelation(a, f, "Biskuit Renyah");
//
//    InsertRelation(ListR, r);
//
//    ShowAllRelation(ListR);

    return 0;
}

void EditActorDataMenu(ListActor &LA)
{
    string title = "Edit Actor Data";
    string opT[] = {"Create New Actor", "Edit an Actor", "Delete All Actor", "Back"};
    int opSize = sizeof(opT) / sizeof(opT[0]);
    menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
    Menu mainMenu = GenerateMenu(title, options);
    int sel = 0;
    do
    {
        ShowMenu(mainMenu, sel);
        if(sel == 0)
        {
            CreateNewActor(LA);
        }
    } while(sel != opSize-1);
}

void EditFilmDataMenu(ListFilm &LF)
{
    string title = "Edit Film Data";
    string opT[] = {"Create New Film", "Edit a Film", "Delete All Film", "Back"};
    int opSize = sizeof(opT) / sizeof(opT[0]);
    menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
    Menu mainMenu = GenerateMenu(title, options);
    int sel = 0;
    do
    {
        ShowMenu(mainMenu, sel);
        if(sel == 0)
        {
            CreateNewFilm(LF);
        }
    } while(sel != opSize-1);
}

void DisplayDataMenu(ListActor LA, ListFilm LF, ListRelation LR)
{
    string title = "Display Data";
    string opT[] = {"Display All Actor", "Display All Film", "Search an Actor", "Search a Film", "Actors With Most Roles", "Films With Most Actors", "Back"};
    int opSize = sizeof(opT) / sizeof(opT[0]);
    menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
    Menu mainMenu = GenerateMenu(title, options);
    int sel = 0;
    do
    {
        ShowMenu(mainMenu, sel);
        if(sel == 0)
        {
            system("cls");
            ShowAllActor(LA);
            cout << "\nPress <ENTER> to go back.";
            cin.get();
        }
        else if(sel == 1)
        {
            system("cls");
            ShowAllFilm(LF);
            cout << "\nPress <ENTER> to go back.";
            cin.get();
        }

    } while(sel != opSize-1);
}

void CreateNewActor(ListActor &LA)
{
    system("cls");
    Cell("Create New Actor", 50, "centre", true, true, true, true);
    cout << '\n';
    string name;
    cout << "Name: ";
    getline(cin, name);
    InsertActor(LA, CreateActor(name));
    cout << "\nCreate new actor success!! Press <ENTER> to go back.";
    cin.get();
}

void CreateNewFilm(ListFilm &LF)
{
    system("cls");
    Cell("Create New Film", 50, "centre", true, true, true, true);
    cout << '\n';
    string name;
    string yearStr;
    int year;
    cout << "Name: ";
    getline(cin, name);
    cout << "Year: ";
    getline(cin, yearStr);
    stringstream(yearStr) >> year;
    InsertFilm(LF, CreateFilm(name, year));
    cout << "\nCreate new film success!! Press <ENTER> to go back.";
    cin.get();
}

