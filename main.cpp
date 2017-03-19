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

void CreateNewActor(ListActor &LA, ListFilm LF, ListRelation &LR);
void CreateNewFilm(ListActor LA, ListFilm &LF, ListRelation &LR);
void CreateNewRelation(ListRelation &LR, a_actor aA, a_film aF);

void SelectActorMenu(ListActor LA, a_actor &a, string info = string());
void SelectFilmMenu(ListFilm LF, a_film &a, string info = string());

void SearchActor(ListActor LA, a_actor &a);
void SearchFilm(ListFilm LF, a_film &a);

void EditActorMenu(ListActor &LA, ListFilm LF, ListRelation &LR, a_actor &a);
void EditFilmMenu(ListActor LA, ListFilm &LF, ListRelation &LR, a_film &a);

void EditActorRoleMenu(ListActor LA, ListFilm LF, ListRelation &LR, a_relation &a);
void EditFilmRoleMenu(ListActor LA, ListFilm LF, ListRelation &LR, a_relation &a);

void EditActorName(ListActor &LA, a_actor a);
void AddActorRole(ListFilm LF, ListRelation &LR, a_actor aA);
void DeleteSingleActor(ListActor &LA, ListRelation &LR, a_actor &a);
void DeleteAllActor(ListActor &LA, ListRelation &LR);

void EditFilmTitle(a_film a);
void EditFilmYear(a_film a);
void AddFilmRole(ListActor LA, ListRelation &LR, a_film aF);
void DeleteSingleFilm(ListFilm &LF, ListRelation &LR, a_film &a);
void DeleteAllFilm(ListFilm &LF, ListRelation &LR);

void EditRelationRole(a_relation a);
void EditRelationActor(ListActor LA, a_relation a);
void EditRelationFilm(ListFilm LF, a_relation a);
void DeleteSingleRelation(ListRelation &LR, a_relation &a);

void ShowActorInfo(ListRelation LR, a_actor a);
void ShowFilmInfo(ListRelation LR, a_film a);

void ListAllActor(ListActor LA, a_actor &a);
void ListAllFilm(ListFilm LF, a_film &a);
void ListAllRole(ListRelation LR);
void ListActorRole(ListRelation LR, a_actor aA, a_relation &a);
void ListFilmRole(ListRelation LR, a_film aF, a_relation &a);

void ListActorWithMostRoles(ListActor LA, ListRelation LR, a_actor &a);
void ListFilmWithMostRoles(ListFilm LF, ListRelation LR, a_film &a);

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
        else if(sel == 3)
        {
            Menu C = ConfirmationDialogue("Are you sure you want to exit?");
            int selB = C.opReturn;
            ShowMenu(C, selB, false);
            if(selB == C.opReturn)
            {
                sel = 0;
            }
        }
    } while(sel != M.opReturn);

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
            CreateNewActor(LA, LF, LR);
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
        else if(sel == 2)
        {
            DeleteAllActor(LA, LR);
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
            CreateNewFilm(LA, LF, LR);
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
        else if(sel ==2)
        {
            DeleteAllFilm(LF, LR);
        }
    } while(sel != M.opReturn);
}

void DisplayDataMenu(ListActor LA, ListFilm LF, ListRelation LR)
{
    const vector<string> opT = {"Display All Actor", "Display All Film", "Search an Actor", "Search a Film", "Actors With Most Roles", "Films With Most Roles", "Display All Roles", "Back"};
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
            a_actor a = NULL;
            SearchActor(LA, a);
            if(a != NULL)
            {
                ShowActorInfo(LR, a);
            }
        }
        else if(sel == 3)
        {
            a_film a = NULL;
            SearchFilm(LF, a);
            if(a != NULL)
            {
                ShowFilmInfo(LR, a);
            }
        }
        else if(sel == 4)
        {
            a_actor a = NULL;
            do
            {
                ListActorWithMostRoles(LA, LR, a);
                if(a != NULL)
                {
                    ShowActorInfo(LR, a);
                }
            } while(a != NULL);
        }
        else if(sel == 5)
        {
            a_film a = NULL;
            do
            {
                ListFilmWithMostRoles(LF, LR, a);
                if(a != NULL)
                {
                    ShowFilmInfo(LR, a);
                }
            } while(a != NULL);
        }
        else if(sel == 6)
        {
            ListAllRole(LR);
        }

    } while(sel != M.opReturn);
}

void CreateNewActor(ListActor &LA, ListFilm LF, ListRelation &LR)
{
    vector<string> opT = {"Name"};
    Menu M = GenerateMenu("Create New Actor\nInsert New Actor Info", opT);
    string name;
    do
    {
        string input;
        InputField(M, input);
        stringstream inputStream(input);
        getline(inputStream, name);
        if(name.empty())
        {
            ShowMessage("Name can't be empty!!");
        }
    } while(name.empty());

    a_actor a = CreateActor(name);
    InsertActor(LA, a);

    opT = {"Yes", "No"};
    M = GenerateMenu("Creating new actor successful!!\nAdd role to this actor (Edit Actor)?", opT);
    int sel = M.opReturn;
    ShowMenu(M, sel, false);
    if(sel == 0)
    {
        EditActorMenu(LA, LF, LR, a);
    }
}

void CreateNewFilm(ListActor LA, ListFilm &LF, ListRelation &LR)
{
    vector<string> opT = {"Title", "Year"};
    Menu M = GenerateMenu("Create New Film\nInsert New Film Info", opT);
    string title, yearStr;
    int year = 0;
    do
    {
        string input;
        InputField(M, input);
        stringstream inputStream(input);
        getline(inputStream, title);
        getline(inputStream, yearStr);
        stringstream(yearStr) >> year;
        if(title.empty() || year == 0)
        {
            ShowMessage("Title or year can't be empty!!");
        }
    } while(title.empty() || year == 0);

    a_film a = CreateFilm(title, year);
    InsertFilm(LF, a);

    opT = {"Yes", "No"};
    M = GenerateMenu("Creating new film successful!!\nAdd role to this film (Edit Film)?", opT);
    int sel = M.opReturn;
    ShowMenu(M, sel, false);
    if(sel == 0)
    {
        EditFilmMenu(LA, LF, LR, a);
    }
}

void CreateNewRelation(ListRelation &LR, a_actor aA, a_film aF)
{
    vector<string> opT = {"Role"};
    string title = "Add Role by [" + aA->info.name + "] in\n" + '[' + aF->info.title + " (" + to_string(aF->info.year) + ")]";
    Menu M = GenerateMenu(title, opT);
    string role;
    do
    {
        string input;
        InputField(M, input);
        stringstream inputStream(input);
        getline(inputStream, role);
        if(role.empty())
        {
            ShowMessage("Role can't be empty!!");
        }
    } while(role.empty());

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
        else if(sel == 1)
        {
            ListAllActor(LA, a);
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
        else if(sel == 1)
        {
            ListAllFilm(LF, a);
        }
    } while((sel != M.opReturn) && (a == NULL));
}

void SearchActor(ListActor LA, a_actor &a)
{
    bool done = false;
    while(!done)
    {
        vector<string> opT = {"Search"};
        Menu M = GenerateMenu("Search Actor by Name", opT);
        string searchName;
        do
        {

            string input;
            InputField(M, input);
            stringstream inputStream(input);
            getline(inputStream, searchName);
            if(searchName.empty())
            {
                ShowMessage("Name is empty!!");
            }

        } while(searchName.empty());

        vector<a_actor> aT = GetAllActorWithStr(LA, searchName);
        if(!aT.empty())
        {
            vector<string> opT;
            for(const a_actor &aA: aT)
            {
                opT.push_back(aA->info.name);
            }
            opT.push_back("Back");

            if(aT.size() <= 1)
            {
                M = GenerateMenu('"' + searchName + "\" found in one actor.", opT);
            }
            else
            {
                M = GenerateMenu('"' + searchName + "\" found in " +  to_string(aT.size()) + " actors.", opT);
            }
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
            done = true;
        }
        else
        {
            Menu C = ConfirmationDialogue('"' + searchName + "\" couldn't be found.\nSearch Again?");
            int sel = 0;
            ShowMenu(C, sel, false);
            if(sel == C.opReturn)
            {
                done = true;
            }
        }
    }
}

void SearchFilm(ListFilm LF, a_film &a)
{
    bool done = false;
    while(!done)
    {
        vector<string> opT = {"Search"};
        Menu M = GenerateMenu("Search Film by Title", opT);
        string searchTitle;
        do
        {

            string input;
            InputField(M, input);
            stringstream inputStream(input);
            getline(inputStream, searchTitle);
            if(searchTitle.empty())
            {
                ShowMessage("Name is empty!!");
            }

        } while(searchTitle.empty());

        vector<a_film> aT = GetAllFilmWithStr(LF, searchTitle);
        if(!aT.empty())
        {
            vector<string> opT;
            for(const a_film &aF: aT)
            {
                opT.push_back(aF->info.title + " (" + to_string(aF->info.year) + ')');
            }
            opT.push_back("Back");

            if(aT.size() <= 1)
            {
                M = GenerateMenu('"' + searchTitle + "\" found in one film.", opT);
            }
            else
            {
                M = GenerateMenu('"' + searchTitle + "\" found in " +  to_string(aT.size()) + " films.", opT);
            }
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
            done = true;
        }
        else
        {
            Menu C = ConfirmationDialogue('"' + searchTitle + "\" couldn't be found.\nSearch Again?");
            int sel = 0;
            ShowMenu(C, sel, false);
            if(sel == C.opReturn)
            {
                done = true;
            }
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
            a_relation aR = NULL;
            ListActorRole(LR, a, aR);
            if(aR != NULL)
            {
                EditActorRoleMenu(LA, LF, LR, aR);
            }
        }
        else if(sel == 3)
        {
            DeleteSingleActor(LA, LR, a);
        }
    } while(sel != M.opReturn && a != NULL);
}

void EditFilmMenu(ListActor LA, ListFilm &LF, ListRelation &LR, a_film &a)
{
    vector<string> opT = {"Edit Title", "Edit Year", "Add Role", "Edit Roles", "Delete Film", "Back"};
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
            AddFilmRole(LA, LR, a);
        }
        else if(sel == 3)
        {
            a_relation aR = NULL;
            ListFilmRole(LR, a, aR);
            if(aR != NULL)
            {
                EditFilmRoleMenu(LA, LF, LR, aR);
            }
        }
        else if(sel == 4)
        {
            DeleteSingleFilm(LF, LR, a);
        }
    } while(sel != M.opReturn && a != NULL);
}

void EditActorRoleMenu(ListActor LA, ListFilm LF, ListRelation &LR, a_relation &a)
{
    vector<string> opT = {"Edit Role Name", "Change Film", "Delete Role", "Back"};
    Menu M;
    int sel = 0;
    do
    {
        a_actor aA = a->info.r_actor;
        a_film aF = a->info.r_film;
        string title = "Edit [" + aA->info.name + "]'s Role Data\n\"" + a->info.role + "\" in " + aF->info.title + " (" + to_string(aF->info.year) + ')';
        M = GenerateMenu(title, opT);
        ShowMenu(M, sel);
        if(sel == 0)
        {
            EditRelationRole(a);
        }
        else if(sel == 1)
        {
            EditRelationFilm(LF, a);
        }
        else if(sel == 2)
        {
            DeleteSingleRelation(LR, a);
        }
    } while(sel != M.opReturn && a != NULL);
}

void EditFilmRoleMenu(ListActor LA, ListFilm LF, ListRelation &LR, a_relation &a)
{
    vector<string> opT = {"Edit Role Name", "Change Actor", "Delete Role", "Back"};
    Menu M;
    int sel = 0;
    do
    {
        a_actor aA = a->info.r_actor;
        a_film aF = a->info.r_film;
        string title = "Edit [" + aF->info.title + " (" + to_string(aF->info.year) + ")]'s Actor Data\n" + aA->info.name + " as \"" + a->info.role + '"';
        M = GenerateMenu(title, opT);
        ShowMenu(M, sel);
        if(sel == 0)
        {
            EditRelationRole(a);
        }
        else if(sel == 1)
        {
            EditRelationActor(LA, a);
        }
        else if(sel == 2)
        {
            DeleteSingleRelation(LR, a);
        }
    } while(sel != M.opReturn && a != NULL);
}

void EditActorName(ListActor &LA, a_actor a)
{
    vector<string> opT = {"New Name"};
    Menu M = GenerateMenu("Edit Actor's Name\n[" + a->info.name + ']', opT);
    string name;
    do
    {
        string input;
        InputField(M, input);
        stringstream inputStream(input);
        getline(inputStream, name);
        if(name.empty())
        {
            ShowMessage("Name can't be empty!!");
        }
    } while(name.empty());

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
    ShowMenu(C, sel, false);
    if(sel == 0)
    {
        DeleteAllRelationWithActor(LR, a);
        DeleteActor(LA, a);
        DeallocateActor(a);
        ShowMessage("Delete actor successful!!");
    }
}

void DeleteAllActor(ListActor &LA, ListRelation &LR)
{
    Menu C = ConfirmationDialogue("Are you sure you want to delete ALL actors?");
    int sel = C.opReturn;
    ShowMenu(C, sel, false);
    if(sel == 0)
    {
        if(LA.first != NULL)
        {
            while(LA.first != NULL)
            {
                a_actor a = LA.first;
                DeleteAllRelationWithActor(LR, a);
                DeleteActor(LA, a);
                DeallocateActor(a);
            }
            ShowMessage("Delete all actors successful!!");
        }
        else
        {
            ShowMessage("Data of actor is empty!!");
        }
    }
}

void EditFilmTitle(a_film a)
{
    vector<string> opT = {"New Title"};
    Menu M = GenerateMenu("Edit Film's Title\n[" + a->info.title + " (" + to_string(a->info.year) + ")]", opT);
    string title;
    do
    {
        string input;
        InputField(M, input);
        stringstream inputStream(input);
        getline(inputStream, title);
        if(title.empty())
        {
            ShowMessage("Title can't be empty!!");
        }
    } while(title.empty());

    a->info.title = title;
    ShowMessage("Edit film's title successful!!");
}

void EditFilmYear(a_film a)
{
    vector<string> opT = {"New Year"};
    Menu M = GenerateMenu("Edit Film's Year\n[" + a->info.title + " (" + to_string(a->info.year) + ")]", opT);
    int year = 0;
    do
    {
        string input;
        InputField(M, input);
        stringstream inputStream(input);
        inputStream >> year;
        if(year == 0)
        {
            ShowMessage("Year can't be empty!!");
        }
    } while(year == 0);

    a->info.year = year;
    ShowMessage("Edit film's year successful!!");
}

void AddFilmRole(ListActor LA, ListRelation &LR, a_film aF)
{
    a_actor aA = NULL;
    SelectActorMenu(LA, aA, "Add Role to [" + aF->info.title + " (" + to_string(aF->info.year) + ")]");
    if(aA != NULL)
    {
        CreateNewRelation(LR, aA, aF);
    }
}

void DeleteSingleFilm(ListFilm &LF, ListRelation &LR, a_film &a)
{
    Menu C = ConfirmationDialogue("Are you sure you want to delete\n[" + a->info.title + " (" + to_string(a->info.year) + ")] ?");
    int sel = C.opReturn;
    ShowMenu(C, sel, false);
    if(sel == 0)
    {
        DeleteAllRelationWithFilm(LR, a);
        DeleteFilm(LF, a);
        DeallocateFilm(a);
        ShowMessage("Delete film successful!!");
    }
}

void DeleteAllFilm(ListFilm &LF, ListRelation &LR)
{
    Menu C = ConfirmationDialogue("Are you sure you want to delete ALL films?");
    int sel = C.opReturn;
    ShowMenu(C, sel, false);
    if(sel == 0)
    {
        if(LF.first != NULL)
        {
            while(LF.first != NULL)
            {
                a_film a = LF.first;
                DeleteAllRelationWithFilm(LR, a);
                DeleteFilm(LF, a);
                DeallocateFilm(a);
            }
            ShowMessage("Delete all films successful!!");
        }
        else
        {
            ShowMessage("Data of film is empty!!");
        }
    }
}

void EditRelationRole(a_relation a)
{
    vector<string> opT = {"New Role"};
    a_actor aA = a->info.r_actor;
    a_film aF = a->info.r_film;
    string title = "Edit Role by [" + aA->info.name + "] in\n" + '[' + aF->info.title + " (" + to_string(aF->info.year) + ")]";
    Menu M = GenerateMenu(title, opT);
    string role;
    do
    {
        string input;
        InputField(M, input);
        stringstream inputStream(input);
        getline(inputStream, role);
        if(role.empty())
        {
            ShowMessage("Role can't be empty!!");
        }
    } while(role.empty());

    a->info.role = role;
    ShowMessage("Edit role successful!!");
}

void EditRelationActor(ListActor LA, a_relation a)
{
    a_actor aA = NULL;
    SelectActorMenu(LA, aA, "Change the Actor of The Role");
    if(aA != NULL)
    {
        a->info.r_actor = aA;
        ShowMessage("Change actor successful!!");
    }
}

void EditRelationFilm(ListFilm LF, a_relation a)
{
    a_film aF = NULL;
    SelectFilmMenu(LF, aF, "Change the Film of The Role");
    if(aF != NULL)
    {
        a->info.r_film = aF;
        ShowMessage("Change film successful!!");
    }
}

void DeleteSingleRelation(ListRelation &LR, a_relation &a)
{
    Menu C = ConfirmationDialogue("Are you sure you want to delete the role?");
    int sel = C.opReturn;
    ShowMenu(C, sel, false);
    if(sel == 0)
    {
        DeleteRelation(LR, a);
        DeallocateRelation(a);
        ShowMessage("Delete role successful!!");
    }
}

void ShowActorInfo(ListRelation LR, a_actor a)
{
    string info = "[Actor Info]\n" + a->info.name;
    vector<a_relation> relations = GetAllRelationWithActor(LR, a);
    if(!relations.empty())
    {
        info += "\n\n[Roles]";
        for(const a_relation &aR: relations)
        {
            a_film aF = aR->info.r_film;
            info += "\n\"" + aR->info.role + "\" in " + aF->info.title + " (" + to_string(aF->info.year) + ')';
        }
    }
    else
    {
        info += "\n\nThis actor doesn't have any role.";
    }

    vector<string> opT = {"Back"};
    Menu M = GenerateMenu(info, opT);
    int sel = 0;
    ShowMenu(M, sel, false);
}

void ShowFilmInfo(ListRelation LR, a_film a)
{
    string info = "[Film Info]\n" + a->info.title + " (" + to_string(a->info.year) + ')';
    vector<a_relation> relations = GetAllRelationWithFilm(LR, a);
    if(!relations.empty())
    {
        info += "\n\n[Roles]";
        for(const a_relation &aR: relations)
        {
            a_actor aA = aR->info.r_actor;
            info += "\n\"" + aR->info.role + "\" by " + aA->info.name;
        }
    }
    else
    {
        info += "\n\nThis film doesn't have any role.";
    }

    vector<string> opT = {"Back"};
    Menu M = GenerateMenu(info, opT);
    int sel = 0;
    ShowMenu(M, sel, false);
}

void ListAllActor(ListActor LA, a_actor &a)
{
    a = NULL;
    vector<a_actor> aT = GetAllActorAddress(LA);
    if(!aT.empty())
    {
        vector<string> opT;
        for(const a_actor &aA: aT)
        {
            opT.push_back(aA->info.name);
        }
        opT.push_back("Back");
        Menu M = GenerateMenu("All Actors", opT);
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
        ShowMessage("Data of actor is empty!!");
    }
}

void ListAllFilm(ListFilm LF, a_film &a)
{
    a = NULL;
    vector<a_film> aT = GetAllFilmAddress(LF);
    if(!aT.empty())
    {
        vector<string> opT;
        for(const a_film &aF: aT)
        {
            opT.push_back(aF->info.title + " (" + to_string(aF->info.year) + ')');
        }
        opT.push_back("Back");
        Menu M = GenerateMenu("All Films", opT);
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
        ShowMessage("Data of film is empty!!");
    }
}

void ListAllRole(ListRelation LR)
{
    vector<a_relation> aT = GetAllRelationAddress(LR);
    if(!aT.empty())
    {
        vector<string> opT;
        for(const a_relation &aR: aT)
        {
            a_actor aA = aR->info.r_actor;
            a_film aF = aR->info.r_film;
            opT.push_back(aR->info.role + " (" + aA->info.name + ") in " + aF->info.title + " (" + to_string(aF->info.year) + ')');
        }
        opT.push_back("Back");
        Menu M = GenerateMenu("All Roles", opT);
        int sel = 0;
        do
        {
            ShowMenu(M, sel);
        } while(sel != M.opReturn);
    }
    else
    {
        ShowMessage("Data of role is empty!!");
    }
}

void ListActorRole(ListRelation LR, a_actor aA, a_relation &a)
{
    a = NULL;
    vector<a_relation> aT = GetAllRelationWithActor(LR, aA);
    if(!aT.empty())
    {
        vector<string> opT;
        for(const a_relation &aR: aT)
        {
            a_film aF = aR->info.r_film;
            opT.push_back(aR->info.role + " in " + aF->info.title + " (" + to_string(aF->info.year) + ')');
        }
        opT.push_back("Back");
        Menu M = GenerateMenu("All [" + aA->info.name + "]'s roles", opT);
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
        ShowMessage('[' + aA->info.name + "] doesn't star in any film.");
    }
}

void ListFilmRole(ListRelation LR, a_film aF, a_relation &a)
{
    a = NULL;
    vector<a_relation> aT = GetAllRelationWithFilm(LR, aF);
    if(!aT.empty())
    {
        vector<string> opT;
        for(const a_relation &aR: aT)
        {
            a_actor aA = aR->info.r_actor;
            opT.push_back(aA->info.name + " as " + aR->info.role);
        }
        opT.push_back("Back");
        Menu M = GenerateMenu("All [" + aF->info.title + "]'s roles", opT);
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
        ShowMessage('[' + aF->info.title + "] doesn't star any actor.");
    }
}

void ListActorWithMostRoles(ListActor LA, ListRelation LR, a_actor &a)
{
    vector<a_actor> aT = GetAllActorAddress(LA);
    if(!aT.empty())
    {
        for(int i = 1; i < aT.size(); i++)
        {
            a_actor aTemp = aT[i];
            int j = i;
            int n = TotalRelationOfActor(LR, aT[i]);
            while(j > 0 && n > TotalRelationOfActor(LR, aT[j-1]))
            {
                aT[j] = aT[j-1];
                j--;
            }
            aT[j] = aTemp;
        }
        vector<string> opT;
        for(const a_actor &aA: aT)
        {
            int n = TotalRelationOfActor(LR, aA);
            if(n <= 1)
            {
                opT.push_back(aA->info.name + " [" + to_string(n) + " role]");
            }
            else
            {
                opT.push_back(aA->info.name + " [" + to_string(n) + " roles]");
            }
        }
        opT.push_back("Back");

        Menu M = GenerateMenu("Actor Ranking Based on The Number of Roles", opT);
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
        ShowMessage("Data of actor is empty!!");
    }
}

void ListFilmWithMostRoles(ListFilm LF, ListRelation LR, a_film &a)
{
    vector<a_film> aT = GetAllFilmAddress(LF);
    if(!aT.empty())
    {
        for(int i = 1; i < aT.size(); i++)
        {
            a_film aTemp = aT[i];
            int j = i;
            int n = TotalRelationOfFilm(LR, aT[i]);
            while(j > 0 && n > TotalRelationOfFilm(LR, aT[j-1]))
            {
                aT[j] = aT[j-1];
                j--;
            }
            aT[j] = aTemp;
        }
        vector<string> opT;
        for(const a_film &aF: aT)
        {
            int n = TotalRelationOfFilm(LR, aF);
            if(n <= 1)
            {
                opT.push_back(aF->info.title + " (" + to_string(aF->info.year) + ") [" + to_string(n) + " role]");
            }
            else
            {
                opT.push_back(aF->info.title + " (" + to_string(aF->info.year) + ") [" + to_string(n) + " roles]");
            }
        }
        opT.push_back("Back");

        Menu M = GenerateMenu("Film Ranking Based on The Number of Roles", opT);
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
        ShowMessage("Data of film is empty!!");
    }
}
