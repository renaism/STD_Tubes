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

void SelectActorMenu(ListActor LA, a_actor &a);
void SearchActor(ListActor LA, a_actor &a);

void EditActorInfo(a_actor a);

int main()
{
    ListActor ListA = CreateListActor();
    ListFilm ListF = CreateListFilm();
    ListRelation ListR = CreateListRelation();

    string title = "Actor and Film Management\nMain Menu";
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
        else if(sel == 1)
        {
            address a = NULL;
            SelectActorMenu(LA, a);
            if(a != )
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
    Cell("Insert New Actor Info", 50, "centre", true, true, true, true);
    COORD posInput = CursorGetPos();
    Cell("   Name:\n", 50, "left", true, true, true, true);
    COORD posEnd = CursorGetPos();

    string name;
    CursorSetPos(posInput.X+4, posInput.Y+2);
    getline(cin, name);
    CursorSetPos(posEnd.X, posEnd.Y);
    InsertActor(LA, CreateActor(name));
    cout << "\nCreate new actor success!! Press <ENTER> to go back.";
    cin.get();
}

void CreateNewFilm(ListFilm &LF)
{
    system("cls");
    Cell("Insert New Film Info", 50, "centre", true, true, true, true);
    COORD posTitleInput = CursorGetPos();
    Cell("   Title:\n\n", 50, "left", true, false, true, true);
    COORD posYearInput = CursorGetPos();
    Cell("   Year :\n", 50, "left", false, true, true, true);
    COORD posEnd = CursorGetPos();

    string title, yearStr;
    int year;
    CursorSetPos(posTitleInput.X+4, posTitleInput.Y+2);
    getline(cin, title);
    CursorSetPos(posYearInput.X+4, posYearInput.Y+1);
    getline(cin, yearStr);
    CursorSetPos(posEnd.X, posEnd.Y);
    stringstream(yearStr) >> year;
    InsertFilm(LF, CreateFilm(title, year));
    cout << "\nCreate new film success!! Press <ENTER> to go back.";
    cin.get();
}

void SelectActorMenu(ListActor LA, a_actor &a)
{
    string title = "Select an Actor";
    string opT[] = {"Search by Name", "Select From List", "Cancel"};
    int opSize = sizeof(opT) / sizeof(opT[0]);
    menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
    Menu mainMenu = GenerateMenu(title, options);
    int sel = 0;
    do
    {
        ShowMenu(mainMenu, sel);
        if(sel == 0)
        {
            SearchActor(LA, a);
        }
    } while((sel != opSize-1) && (a == NULL));
}

void SearchActor(ListActor LA, a_actor &a)
{
    bool done = false;
    while(!done)
    {
        system("cls");
        Cell("Search Actor by Name", 50, "centre", true, true, true, true);
        COORD posInput = CursorGetPos();
        Cell("   Search:\n", 50, "left", true, true, true, true);

        string searchName;
        CursorSetPos(posInput.X+4, posInput.Y+2);
        getline(cin, searchName);
        CursorSetPos(posEnd.X, posEnd.Y);
        a = FindActorByName(LA, searchName);

        string title;
        string opT[];
        if(a != NULL)
        {
            title = '"' + searchName + "\" found!";
            opT[] = {"Continue"};
            done = true;
        }
        else
        {
            title = '"' + searchName + "\" couldn't be found!";
            opT[] = {"Search Again", "Cancel"};
        }
        int opSize = sizeof(opT) / sizeof(opT[0]);
        menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
        Menu mainMenu = GenerateMenu(title, options);
        int sel = 0;
        do
        {
            ShowMenu(mainMenu, sel);
            if((sel == 1) && (!done))
            {
                done = true;
            }
        } while(sel != opSize-1);
    }
}

void EditActorMenu(ListActor &LA, ListRelation &LR, ListFilm LF, a_actor &a)
{
    string title = "Edit Actor Data\n[" + a->info.name + ']';
    string opT[] = {"Edit Name", "Add Role", "Edit Role", "Delete Actor", "Back"};
    int opSize = sizeof(opT) / sizeof(opT[0]);
    menuOptions options(opT, opT + sizeof(opT) / sizeof(opT[0]));
    Menu mainMenu = GenerateMenu(title, options);
    int sel = 0;
    do
    {
        ShowMenu(mainMenu, sel);
        if(sel == 0)
        {
            EditActorInfo(a);
        }
    } while(sel != opSize-1);
}

void EditActorInfo(ListActor &LA, a_actor a)
{
    system("cls");
    string title = "Edit Actor Name\n[" + a->info.name + ']';
    Cell(title, 50, "centre", true, true, true, true);
    COORD posInput = CursorGetPos();
    Cell("   Name:\n", 50, "left", true, false, true, true);
    COORD posEnd = CursorGetPos();

    string name;
    CursorSetPos(posInput.X+4, posInput.Y+2);
    getline(cin, name);
    CursorSetPos(posEnd.X, posEnd.Y);
    DeleteActor(LA, a);
    a->info.name = name;
    InsertActor(LA, a);
    cout << "\nEdit actor info successful!! Press <ENTER> to go back.";
    cin.get();
}

