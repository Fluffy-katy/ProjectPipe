#include "Menu.h"
#include "Utilites.h"

using namespace std;
//---------------Display objects-------------------
void View_Menu(GTS& GasSystem)
{

    while (1) {
        ENTER;
        cout << "0. Back\n" <<
            "1. List of pipes\n" <<
            "2. List of stations\n" <<
            "3. Show all" << endl;


        switch (GetCorrectNumber(0, 3)) {
        case 1: {
            ENTER;
            cout << "----------Pipes-----------" << endl;
            GasSystem.ViewPipes();
            break;
        }
        case 2: {
            ENTER;
            cout << "----------Stations-----------" << endl;
            GasSystem.ViewStations();
            break;
        }
        case 3: {
            ENTER;
            cout << "----------Pipes-----------" << endl;
            GasSystem.ViewPipes();
            ENTER;
            cout << "----------Stations-----------" << endl;
            GasSystem.ViewStations();
            ENTER;
            break;
        }

        case 0: { return; }
        }
        return;
    }
}

//---------------Editing-------------------
void EditOnePipe(GTS& GasSystem)
{
    ENTER;
    cout << "List of pipes:\n";
    GasSystem.ViewPipes();
    cout << "Select the pipe to edit:";
    auto keys = GasSystem.GetIDs(GTS::PIPE);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "No pipe with the specified ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.EditPipes(key);
}

void EditOneStation(GTS& GasSystem) {
    ENTER;
    cout << "List of stations:\n";
    GasSystem.ViewStations();
    cout << "Select the station to edit:";
    auto keys = GasSystem.GetIDs(GTS::STATION);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "No station with the specified ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.EditStations(key);
}

void Edit_Pipes(GTS& GasSystem) {
    if (!GasSystem.HasObject(GTS::PIPE)) { cout << "No available pipes!" << endl; return; }

    cout << "1. Edit a single pipe by selection\n"
        << "2. Edit by filter\n"
        << "0. Exit"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { EditOnePipe(GasSystem); break; }
    case 2: {
        cout << "Select a filter for search:" <<
            "\n1. By name" <<
            "\n2. By state"; ENTER;

        switch (GetCorrectNumber(0, 2))
        {
        case 1:
        {
            GasSystem.Edit_ByName(GTS::PIPE);
            break;
        }
        case 2:
        {
            GasSystem.Edit_ByParametr(GTS::PIPE);
            break;
        }
        case 0: { break; }
        }
        break;
    }
    }
}

void Edit_Stations(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::STATION))
    {
        cout << "No available stations!" << endl;
        return;
    }

    cout << "1. Edit a single station by selection\n"
        << "2. Edit by filter\n"
        << "0. Exit"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { EditOneStation(GasSystem); break; }

    case 2: {
        cout << "Select a filter for search:" <<
            "\n1. By name" <<
            "\n2. By percentage of inactive workshops in the station" <<
            "\n0. Exit"; ENTER;

        switch (GetCorrectNumber(0, 2)) {
        case 1:
        {
            GasSystem.Edit_ByName(GTS::STATION);
            break;
        }
        case 2:
        {
            GasSystem.Edit_ByParametr(GTS::STATION);
            break;
        }
        case 0: { break; }
        }
        break;
    }
    case 0: { break; }
    }
}

void Edit_Menu(GTS& GasSystem)
{
    cout << "1. Edit pipes\n"
        << "2. Edit stations\n"
        << "0. Back"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { Edit_Pipes(GasSystem); break; }
    case 2: { Edit_Stations(GasSystem); break; }
    case 0: { break; }
    }
}

//---------------Delete-------------------

void DeleteOnePipe(GTS& GasSystem)
{
    ENTER;
    cout << "List of pipes:\n";
    GasSystem.ViewPipes();
    cout << "Select the pipe to delete:";
    auto keys = GasSystem.GetIDs(GTS::PIPE);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "No pipe with the specified ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.DeletePipes(key);
}

void DeleteOneStation(GTS& GasSystem) {
    ENTER;
    cout << "List of stations:\n";
    GasSystem.ViewStations();
    cout << "Select the station to delete:";
    auto keys = GasSystem.GetIDs(GTS::STATION);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "No station with the specified ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.DeleteStations(key);
}

void Delete_Pipes(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::PIPE)) { cout << "No available pipes!" << endl; return; }

    cout << "1. Delete a single pipe by selection\n"
        << "2. Delete by filter\n"
        << "0. Exit"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { DeleteOnePipe(GasSystem); break; }
    case 2: {
        cout << "Select a filter for search:" <<
            "\n1. By name" <<
            "\n2. By state"; ENTER;

        switch (GetCorrectNumber(0, 2))
        {
        case 1:
        {
            GasSystem.Delete_ByName(GTS::PIPE);
            break;
        }
        case 2:
        {
            GasSystem.Delete_ByParametr(GTS::PIPE);
            break;
        }
        case 0: { break; }
        }
        break;
    }
    }

}

void Delete_Stations(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::STATION)) { cout << "No available stations!" << endl; return; }

    cout << "1. Delete a single station by selection\n"
        << "2. Delete by filter\n"
        << "0. Exit"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { DeleteOneStation(GasSystem); break; }
    case 2: {
        cout << "Select a filter for search:" <<
            "\n1. By name" <<
            "\n2. By percentage of inactive workshops in the station"; ENTER;

        switch (GetCorrectNumber(0, 2))
        {
        case 1: { GasSystem.Delete_ByName(GTS::STATION); break; }
        case 2: { GasSystem.Delete_ByParametr(GTS::STATION); break; }
        case 0: { break; }
        }
        break;
    }
    }

}

//---------------Deliting-------------------

void Delete_Menu(GTS& GasSystem)
{
    cout << "1. Delete pipes\n"
        << "2. Delete stations\n"
        << "0. Back" << endl;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { Delete_Pipes(GasSystem); break; }
    case 2: { Delete_Stations(GasSystem); break; }
    case 0: { break; }
    }
}


void Graph_Menu(GTS& GasSystem) {
    ENTER;
    cout << "1. Show connections\n" <<
        "2. Add connection\n" <<
        "3. Delete connection\n" <<
        "4. Topological sort\n" <<
        "5. Find shortest way\n" <<
        "6. Find max flow\n" <<
        "0. Exit\n" << endl;

    switch (GetCorrectNumber(0, 6)) {
    case 1: { GasSystem.ViewConnections(); break; }
    case 2: { GasSystem.CreateConnection(); break; }
    case 3: { GasSystem.DeleteConnection(); break; }
    case 4: { GasSystem.TopologicalSort(); break; }
    case 5: { GasSystem.ShortestPath(); break; }
    case 6: { GasSystem.MaxFlow(); break; }
    case 0: { return; }
    }
}


void MainMenu(GTS& GasSystem)
{
    while (1) {
        ENTER;
        cout << "\n1. Add pipe\n" <<
            "2. Add station\n" <<
            "3. View objects\n" <<
            "4. Edit\n" <<
            "5. Delete\n" <<
            "6. Graph\n" <<
            "7. Save\n" <<
            "8. Load\n" <<
            "0. Exit\n" << endl;

        switch (GetCorrectNumber(0, 8))
        {
        case 1: { GasSystem.CreatePipe(); break; }

        case 2: { GasSystem.CreateCS(); break; }

        case 3: { View_Menu(GasSystem); break; }

        case 4: { Edit_Menu(GasSystem); break; }

        case 5: { Delete_Menu(GasSystem); break; }

        case 6: { Graph_Menu(GasSystem); break; }

        case 7: { GasSystem.SaveConfiguration(); break; }

        case 8: { GasSystem.LoadConfiguration(); break; }

        case 0: { return; }
        }
    }
}