#include <iostream>
#include <sstream>

#include "menu.h"

#include "actor.h"
#include "film.h"
#include "relation.h"

using namespace std;

void EditActorDataMenu(ListActor &LA, ListFilm LF, ListRelation &LR);
void EditFilmDataMenu(ListActor LA, ListFilm &LF, ListRelation &LR);
void DisplayDataMenu(ListActor LA, ListFilm LF, ListRelation LR);

void CreateNewActor(ListActor &LA);
void CreateNewFilm(ListFilm &LF);
void CreateNewRelation(ListRelation &LR, a_actor aA, a_film aF);

void SelectActorMenu(ListActor LA, a_actor &a, string info = string());
void SelectFilmMenu(ListFilm LF, a_film &a, string info = string());

void SearchActor(ListActor LA, a_actor &a);
void SearchFilm(ListFilm LF, a_film &a);

void ListAllActor(ListActor LA, a_actor &a);
void ListAllFilm(ListFilm LF, a_film &a);

void ShowActorInfo(ListRelation LR, a_actor a);
void ShowFilmInfo(ListRelation LR, a_film a);

void EditActorMenu(ListActor &LA, ListFilm LF, ListRelation &LR, a_actor &a);
void EditFilmMenu(ListActor LA, ListFilm &LF, ListRelation &LR, a_film &a);

void EditActorName(ListActor &LA, a_actor a);
void AddActorRole(ListFilm LF, ListRelation &LR, a_actor aA);
void DeleteSingleActor(ListActor &LA, ListRelation &LR, a_actor &a);

void EditFilmTitle(a_film a);
void EditFilmYear(a_film a);
void AddFilmActor(ListActor LA, ListRelation &LR, a_film aF);
void DeleteSingleFilm(ListFilm &LF, ListRelation &LR, a_film &a);


int main()
{
    ListActor ListA = CreateListActor();
    ListFilm ListF = CreateListFilm();
    ListRelation ListR = CreateListRelation();

    const vector<string> opT = {"Edit Actor Data", "Edit Film Data", "Display Data", "Exit"};
    Menu M = GenerateMenu("Actor and Film Management\nMain Menu", opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            EditActorDataMenu(ListA, ListF, ListR);
        }
        else if(sel == 1)
        {
            EditFilmDataMenu(ListA, ListF, ListR);
        }
        else if(sel == 2)
        {
            DisplayDataMenu(ListA, ListF, ListR);
        }
    } while(sel != M.opReturn);
    cout << "Program exited." << endl;
    cin.get();

    return 0;
}

void EditActorDataMenu(ListActor &LA, ListFilm LF, ListRelation &LR)
{
    const vector<string> opT = {"Create New Actor", "Edit an Actor", "Delete All Actor", "Back"};
    Menu M = GenerateMenu("Edit Actor Data", opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            CreateNewActor(LA);
        }
        else if(sel == 1)
        {
            a_actor a = NULL;
            SelectActorMenu(LA, a);
            if(a != NULL)
            {
                EditActorMenu(LA, LF, LR, a);
            }
        }
    } while(sel != M.opReturn);
}

void EditFilmDataMenu(ListActor LA, ListFilm &LF, ListRelation &LR)
{
    const vector<string> opT = {"Create New Film", "Edit a Film", "Delete All Film", "Back"};
    Menu M = GenerateMenu("Edit Film Data", opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            CreateNewFilm(LF);
        }
        else if(sel == 1)
        {
            a_film a = NULL;
            SelectFilmMenu(LF, a);
            if(a != NULL)
            {
                EditFilmMenu(LA, LF, LR, a);
            }
        }
    } while(sel != M.opReturn);
}

void DisplayDataMenu(ListActor LA, ListFilm LF, ListRelation LR)
{
    const vector<string> opT = {"Display All Actor", "Display All Film", "Display All Relation","Search an Actor", "Search a Film", "Actors With Most Roles", "Films With Most Actors", "Back"};
    Menu M = GenerateMenu("Display Data", opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            a_actor a = NULL;
            do
            {
                ListAllActor(LA, a);
                if(a != NULL)
                {
                    ShowActorInfo(LR, a);
                }
            } while (a != NULL);
        }
        else if(sel == 1)
        {
            a_film a = NULL;
            do
            {
                ListAllFilm(LF, a);
                if(a != NULL)
                {
                    ShowFilmInfo(LR, a);
                }
            } while (a != NULL);
        }
        else if(sel == 2)
        {
            system("cls");
            ShowAllRelation(LR);
            cout << "\nPress <ENTER> to go back.";
            cin.get();
        }

    } while(sel != M.opReturn);
}

void CreateNewActor(ListActor &LA)
{
    vector<string> opT = {"Name"};
    Menu M = GenerateMenu("Create New Actor\nInsert New Actor Info", opT);
    string input;
    InputField(M, input);

    stringstream inputStream(input);
    string name;
    getline(inputStream, name);

    InsertActor(LA, CreateActor(name));
    ShowMessage("Creating new actor successful!!");
}

void CreateNewFilm(ListFilm &LF)
{
    vector<string> opT = {"Title", "Year"};
    Menu M = GenerateMenu("Create New Film\nInsert New Film Info", opT);
    string input;
    InputField(M, input);

    stringstream inputStream(input);
    string title, yearStr;
    int year;
    getline(inputStream, title);
    getline(inputStream, yearStr);
    stringstream(yearStr) >> year;

    InsertFilm(LF, CreateFilm(title, year));
    ShowMessage("Creating new film successful!!");
}

void CreateNewRelation(ListRelation &LR, a_actor aA, a_film aF)
{
    vector<string> opT = {"Role"};
    string title = "Add Role by [" + aA->info.name + "] in\n" + '[' + aF->info.title + " (" + to_string(aF->info.year) + ")]";
    Menu M = GenerateMenu(title, opT);
    string input;
    InputField(M, input);

    stringstream inputStream(input);
    string role;
    getline(inputStream, role);

    InsertRelation(LR, CreateRelation(aA, aF, role));
    ShowMessage("Adding role successful!!");
}

void SelectActorMenu(ListActor LA, a_actor &a, string info)
{
    if(!info.empty()) info += '\n';
    vector<string> opT = {"Search by Name", "Select From List", "Cancel"};
    Menu M = GenerateMenu(info + "Select an Actor", opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            SearchActor(LA, a);
        }
    } while((sel != M.opReturn) && (a == NULL));
}

void SelectFilmMenu(ListFilm LF, a_film &a, string info)
{
    if(!info.empty()) info += '\n';
    vector<string> opT = {"Search by Title", "Select From List", "Cancel"};
    Menu M = GenerateMenu(info + "Select a Film", opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            SearchFilm(LF, a);
        }
    } while((sel != M.opReturn) && (a == NULL));
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
        COORD posEnd = CursorGetPos();

        string searchName;
        CursorSetPos(posInput.X+4, posInput.Y+2);
        getline(cin, searchName);
        CursorSetPos(posEnd.X, posEnd.Y);
        a = FindActorByName(LA, searchName);

        string title = '"' + searchName + '"';
        vector<string> opT;
        if(a != NULL)
        {
            title += " found!";
            opT = {"Continue"};
            done = true;
        }
        else
        {
            title += " couldn't be found!";
            opT = {"Search Again", "Cancel"};
        }

        Menu M = GenerateMenu(title, opT);
        int sel = 0;
        ShowMenu(M, sel);
        if((sel == 1) && (!done))
        {
            done = true;
        }
    }
}

void SearchFilm(ListFilm LF, a_film &a)
{
    bool done = false;
    while(!done)
    {
        system("cls");
        Cell("Search Film by Title", 50, "centre", true, true, true, true);
        COORD posInput = CursorGetPos();
        Cell("   Search:\n", 50, "left", true, true, true, true);
        COORD posEnd = CursorGetPos();

        string searchTitle;
        CursorSetPos(posInput.X+4, posInput.Y+2);
        getline(cin, searchTitle);
        CursorSetPos(posEnd.X, posEnd.Y);
        a = FindFilmByTitle(LF, searchTitle);

        string title = '"' + searchTitle + '"';
        vector<string> opT;
        if(a != NULL)
        {
            title += " found!";
            opT = {"Continue"};
            done = true;
        }
        else
        {
            title += " couldn't be found!";
            opT = {"Search Again", "Cancel"};
        }

        Menu M = GenerateMenu(title, opT);
        int sel = 0;
        ShowMenu(M, sel);
        if((sel == 1) && (!done))
        {
            done = true;
        }
    }
}

void EditActorMenu(ListActor &LA, ListFilm LF, ListRelation &LR, a_actor &a)
{
    vector<string> opT = {"Edit Name", "Add Role", "Edit Role", "Delete Actor", "Back"};
    Menu M = GenerateMenu("Edit Actor Data\n[" + a->info.name + ']', opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            EditActorName(LA, a);
            M.title = "Edit Actor Data\n[" + a->info.name + ']';
        }
        else if(sel == 1)
        {
            AddActorRole(LF, LR, a);
        }
        else if(sel == 2)
        {

        }
        else if(sel == 3)
        {
            DeleteSingleActor(LA, LR, a);
        }
    } while(sel != M.opReturn && a != NULL);
}

void EditFilmMenu(ListActor LA, ListFilm &LF, ListRelation &LR, a_film &a)
{
    vector<string> opT = {"Edit Title", "Edit Year", "Add Actor", "Edit Actors", "Delete Film", "Back"};
    Menu M = GenerateMenu("Edit Film Data\n[" + a->info.title + " (" + to_string(a->info.year) + ")]", opT);
    int sel = 0;
    do
    {
        ShowMenu(M, sel);
        if(sel == 0)
        {
            EditFilmTitle(a);
            M.title = "Edit Film Data\n[" + a->info.title + " (" + to_string(a->info.year) + ")]";
        }
        else if(sel == 1)
        {
            EditFilmYear(a);
            M.title = "Edit Film Data\n[" + a->info.title + " (" + to_string(a->info.year) + ")]";
        }
        else if(sel == 2)
        {
            AddFilmActor(LA, LR, a);
        }
        else if(sel == 4)
        {
            DeleteSingleFilm(LF, LR, a);
        }
    } while(sel != M.opReturn && a != NULL);
}

void EditActorName(ListActor &LA, a_actor a)
{
    vector<string> opT = {"New Name"};
    Menu M = GenerateMenu("Edit Actor's Name\n[" + a->info.name + ']', opT);
    string input;
    InputField(M, input);

    stringstream inputStream(input);
    string name;
    getline(inputStream, name);

    DeleteActor(LA, a);
    a->info.name = name;
    InsertActor(LA, a);
    ShowMessage("Edit actor's name successful!!");
}

void AddActorRole(ListFilm LF, ListRelation &LR, a_actor aA)
{
    a_film aF = NULL;
    SelectFilmMenu(LF, aF, "Add Role to [" + aA->info.name + ']');
    if(aF != NULL)
    {
        CreateNewRelation(LR, aA, aF);
    }
}



void DeleteSingleActor(ListActor &LA, ListRelation &LR, a_actor &a)
{
    Menu C = ConfirmationDialogue("Are you sure you want to delete\n[" + a->info.name + "] ?");
    int sel = C.opReturn;
    ShowMenu(C, sel);
    if(sel == 0)
    {
        DeleteAllRelationWithActor(LR, a);
        DeleteActor(LA, a);
        DeallocateActor(a);
        ShowMessage("Delete actor successful!!");
    }
}

void EditFilmTitle(a_film a)
{
    vector<string> opT = {"New Title"};
    Menu M = GenerateMenu("Edit Film's Title\n[" + a->info.title + " (" + to_string(a->info.year) + ")]", opT);
    string input;
    InputField(M, input);

    stringstream inputStream(input);
    string title;
    getline(inputStream, title);

    a->info.title = title;
    ShowMessage("Edit film's title successful!!");
}

void EditFilmYear(a_film a)
{
    vector<string> opT = {"New Year"};
    Menu M = GenerateMenu("Edit Film's Year\n[" + a->info.title + " (" + to_string(a->info.year) + ")]", opT);
    string input;
    InputField(M, input);

    stringstream inputStream(input);
    string yearStr;
    int year;
    getline(inputStream, yearStr);
    stringstream(yearStr) >> year;

    a->info.year = year;
    ShowMessage("Edit film's year successful!!");
}

void AddFilmActor(ListActor LA, ListRelation &LR, a_film aF)
{
    a_actor aA = NULL;
    SelectActorMenu(LA, aA, "Add Actor to [" + aF->info.title + " (" + to_string(aF->info.year) + ")]");
    if(aA != NULL)
    {
        CreateNewRelation(LR, aA, aF);
    }
}

void DeleteSingleFilm(ListFilm &LF, ListRelation &LR, a_film &a)
{
    Menu C = ConfirmationDialogue("Are you sure you want to delete\n[" + a->info.title + " (" + to_string(a->info.year) + ")] ?");
    int sel = C.opReturn;
    ShowMenu(C, sel);
    if(sel == 0)
    {
        DeleteAllRelationWithFilm(LR, a);
        DeleteFilm(LF, a);
        DeallocateFilm(a);
        ShowMessage("Delete film successful!!");
    }
}

void ShowActorInfo(ListRelation LR, a_actor a)
{
    string info = "[Actor Info]\n" + a->info.name;
    vector<a_relation> relations = GetAllRelationWithActor(LR, a);
    if(!relations.empty())
    {
        info += "\n\n[Roles]";
        for(const a_relation aR: relations)
        {
            a_film aF = aR->info.r_film;
            info += '\n' + aR->info.role + " in " + aF->info.title + " (" + to_string(aF->info.year) + ')';
        }
    }
    else
    {
        info += "\n\nThis actor doesn't star in any film.";
    }

    vector<string> opT = {"Back"};
    Menu M = GenerateMenu(info, opT);
    int sel = 0;
    ShowMenu(M, sel);
}

void ShowFilmInfo(ListRelation LR, a_film a)
{
    string info = "[Film Info]\n" + a->info.title + " (" + to_string(a->info.year) + ')';
    vector<a_relation> relations = GetAllRelationWithFilm(LR, a);
    if(!relations.empty())
    {
        info += "\n\n[Actors]";
        for(const a_relation aR: relations)
        {
            a_actor aA = aR->info.r_actor;
            info += '\n' + aA->info.name + " as " + aR->info.role;
        }
    }
    else
    {
        info += "\n\nThis film doesn't star any actor.";
    }

    vector<string> opT = {"Back"};
    Menu M = GenerateMenu(info, opT);
    int sel = 0;
    ShowMenu(M, sel);
}

void ListActorRole(ListRelation LR, a_actor aA, a_relation &a)
{
    a = NULL;
    vector<a_relation> aT = GetAllRelationWithActor(LR, aA);
    vector<string> opT;
    Menu M;
    if(!aT.empty())
    {
        for(const a_relation &aR: aT)
        {
            a_film aF = aR->info.r_film;
            opT.push_back(aR->info.role + " in " + aF->info.title + " (" + to_string(aF->info.year) + ')');
        }
        opT.push_back("Back");
        M = GenerateMenu("All [" + aA->info.name + "]'s roles", opT);
        int sel = 0;
        ShowMenu(M, sel);
        if(sel != M.opReturn)
        {
            a = aT[sel];
        }
        else
        {
            a = NULL;
        }
    }
    else
    {
        opT = {"Back"};
        M = GenerateMenu('[' + aA->info.name + "] doesn't star in any film", opT);
        int sel = 0;
        ShowMenu(M, sel);
    }
}

void ListAllActor(ListActor LA, a_actor &a)
{
    a = NULL;
    vector<a_actor> aT = GetAllActorAddress(LA);
    vector<string> opT;
    Menu M;
    if(!aT.empty())
    {
        for(const a_actor &aA: aT)
        {
            opT.push_back(aA->info.name);
        }
        opT.push_back("Back");
        M = GenerateMenu("All Actors", opT);
        int sel = 0;
        ShowMenu(M, sel);
        if(sel != M.opReturn)
        {
            a = aT[sel];
        }
        else
        {
            a = NULL;
        }
    }
    else
    {
        opT = {"Back"};
        M = GenerateMenu("Data of actors is empty!", opT);
        int sel = 0;
        ShowMenu(M, sel);
    }
}

void ListAllFilm(ListFilm LF, a_film &a)
{
    a = NULL;
    vector<a_film> aT = GetAllFilmAddress(LF);
    vector<string> opT;
    Menu M;
    if(!aT.empty())
    {
        for(const a_film &aF: aT)
        {
            opT.push_back(aF->info.title + " (" + to_string(aF->info.year) + ')');
        }
        opT.push_back("Back");
        M = GenerateMenu("All Films", opT);
        int sel = 0;
        ShowMenu(M, sel);
        if(sel != M.opReturn)
        {
            a = aT[sel];
        }
        else
        {
            a = NULL;
        }
    }
    else
    {
        opT = {"Back"};
        M = GenerateMenu("Data of films is empty!", opT);
        int sel = 0;
        ShowMenu(M, sel);
    }
}
