#include "Utilites.h"
#include "Pipe.h"
#include "Station.h"
#include "GTS.h"
#include <format>


using namespace std;


//---------------Filter realisation-------------------

template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repair) {
    return pipe.in_repair == in_repair;
}

bool CheckByWorkshop(Station& station, int cent_non_active) {
    return station.GetUnactiveWorkshop() >= cent_non_active;
}

template <typename Element, typename Parametr>
set<int> Find_By_Filter(unordered_map<int, Element>& elements, Filter<Element, Parametr> filter, Parametr parametr)
{
    set<int> result;
    for (auto& element : elements)
    {
        if (filter(element.second, parametr))
            result.insert(element.second.GetID());
    }
    return result;
}


//util
GTS::GTS()
{}



//---------------Creating obj-------------------
void GTS::CreatePipe()
{
    Pipe pipe;
    pipe.WriteInfo();
    pipes.insert({ pipe.GetID(), pipe });
}


void GTS::CreateCS()
{
    Station station;
    station.WriteInfo();
    stations.insert({ station.GetID(), station });
}


//---------------Show obj-------------------
void GTS::View()
{

    while (1) {
        ENTER;
        cout << "0. Exit\n" <<
            "1. Show pipe\n" <<
            "2. Show CS\n" <<
            "3. Show all" << endl;


        switch (GetCorrectNumber(cin, 0, 3)) {
        case 1: {
            ENTER;
            cout << "----------Pipes-----------" << endl;
            ViewComponents<Pipe>(pipes);

            break;
        }
        case 2: {
            ENTER;
            cout << "----------CS-----------" << endl;
            ViewComponents<Station>(stations);

            break;
        }

        case 3: {
            ENTER;
            cout << "----------Pipes-----------" << endl;
            ViewComponents<Pipe>(pipes);
            ENTER;
            cout << "----------CS-----------" << endl;
            ViewComponents<Station>(stations);
            ENTER;
            break;
        }

        case 0: {
            return;
        }
        }

        return;
    }
}


//---------------Filter-------------------
template <typename Struct>
using Searching = set<int>(*)(Struct& structure);

template <typename Struct>
set<int> Search_By_Name(unordered_map<int, Struct>& structure)
{
    string name = input_string(cin);


    set<int> result = Find_By_Filter<Struct, string>(structure, CheckByName, name);
    return result;
}

template <typename Struct>set<int> Search_By_Status(unordered_map<int, Struct>& structure)
{
    set<int> result = Find_By_Filter<Struct, bool>(structure, CheckByStatus, GetCorrectNumber(cin, 0, 1));
    return result;
}

template <typename Struct>
set<int> Search_By_Workshop(unordered_map<int, Struct>& structure)
{
    set<int> result = Find_By_Filter<Struct, int>(structure, CheckByWorkshop, GetCorrectNumber(cin, 0, 100));
    return result;
}

/*
bool GTS::SearchPipe(Searching<Pipe> search)
{
    ENTER;
    cout << "Enter pipe's name:" << endl;
    vector<int> result = search(pipes);

    if (!result.size())
    {
        cout << "No suitable pipes";
        return false;
    }

    ViewComponentsByID(result, pipes);
    return true;
}
*/


void GTS::Search()
{
    cout << "1. Search pipes\n"
        << "2. Search stations\n"
        << "0. Back" << endl;



    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        SearchPipes();
        break;
    }
    case 2:
    {
        SearchCS();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::SearchPipes()
{
    cout << "Select filter:" <<
        "\n0. To menu" <<
        "\n1. By name" <<
        "\n2. By status" << endl;
    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "Enter the name of the pipe:" << endl;
        set<int> result = Search_By_Name(pipes);

        if (!result.size())
        {
            cout << "No matching pipes found.";
        }

        ViewComponentsByID(result, pipes);
        break;
    }
    case 2:
    {
        ENTER;
        cout << "Enter the status of the pipe:" << endl;
        set<int> result = Search_By_Status(pipes);
        if (!result.size())
        {
            cout << "No matching pipes found.";
            return;
        }
        ViewComponentsByID(result, pipes);
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::SearchCS()
{
    cout << "Select filter:" <<
        "\n0. To menu" <<
        "\n1. By name" <<
        "\n2. By number of workshops" << endl;
    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "Enter the name of the station:" << endl;
        set<int> result = Search_By_Name(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).ShowInfo();

        }
        else cout << "No matching stations found.";
        break;
    }
    case 2:
    {
        ENTER;
        cout << "Enter the non-working workshop:" << endl;
        set<int> result = Search_By_Workshop(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).ShowInfo();
        }
        else cout << "No matching stations found.";
        break;
    }
    case 0:
    {
        break;
    }
    }
}


//---------------Editing-------------------
void GTS::Edit()
{
    cout << "1. Editing of pipes\n"
        << "2. Editing of stations\n"
        << "0. Exit" << endl;


    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        EditPipes();
        break;
    }
    case 2:
    {
        EditCS();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::EditPipes()
{
    if (!pipes.size())
    {
        cout << "No available pipes!\n" << endl;
        return;
    }

    cout << "1. Editing pipe by name\n"
        << "2. Editing by status\n"
        << "0. Exit" << endl;


    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        EditOnePipe();
        break;
    }
    case 2:
    {
        EditSomePipes();
        break;
    }
    case 0:
    {
        break;
    }
    }

}
void GTS::EditCS() {
    if (!stations.size()) {
        cout << "No available stations!\n" << endl;
        return;
    }

    cout << "1. Editing station by name\n"
        << "2. Editing by workshop\n"
        << "0. Exit" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        EditOneCS();
        break;
    }
    case 2:
    {
        EditSomeCS();
        break;
    }
    case 0:
    {
        break;
    }
    }

}


void GTS::EditOnePipe()
{
    ENTER;
    cout << "List of pipes:\n";
    ViewComponents(pipes);
    cout << "Select the pipe to edit:";
    EditOne(pipes);
}

void GTS::EditOneCS()
{
    ENTER;
    cout << "List of stations:\n";
    ViewComponents(stations);
    cout << "Select the station to edit:";
    EditOne(stations);
}

set<int> GetEditNumbers(istream& in, set<int> result)
{
    set<int> IDs;
    int id;
    int Max_ID = Pipe::GetMaxId();
    do {
        id = GetCorrectNumber(cin, 0, Max_ID);
        if (result.contains(id)) {
            IDs.insert(id);
        }
    } while (id != 0);

    return IDs;
}


void GTS::EditSomePipes()
{
    if (!pipes.size())
    {
        cout << "No available pipes!";
        return;
    }

    cout << "Select filter type:" <<
        "\n1. By name" <<
        "\n2. By status" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "Enter the pipe name:" << endl;
        set<int> result = Search_By_Name(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).ShowInfo();

            cout << "Select all(0) or enter IDs (enter IDs in the order to edit, enter 0 to cancel):" << endl;
            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) pipes.at(id).ShowInfo();

            cout << "Select pipe status(0 - no, 1 - yes):" << endl;
            int answer = GetCorrectNumber(cin, 0, 1);
            if (numbers.empty())
            {
                for (auto& id : result) pipes.at(id).Edit(answer);
            }
            else
            {
                for (auto& id : numbers) pipes.at(id).Edit(answer);

            }

        }
        else cout << "No matching pipes";
        break;
    }
    case 2:
    {
        ENTER;
        cout << "Enter the pipe status:" << endl;
        set<int> result = Search_By_Status(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).ShowInfo();

            cout << "Select all(0) or enter IDs (enter IDs in the order to edit, enter 0 to cancel):" << endl;
            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) pipes.at(id).ShowInfo();

            cout << "Select pipe status(0 - no, 1 - yes):" << endl;
            int answer = GetCorrectNumber(cin, 0, 1);
            if (numbers.empty())
            {
                for (auto& id : result) pipes.at(id).Edit(answer);
            }
            else
            {
                for (auto& id : numbers) pipes.at(id).Edit(answer);

            }
        }
        else cout << "No matching pipes";
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::EditSomeCS()
{
    if (!pipes.size())
    {
        cout << "No matching stations!";
        return;
    }

    cout << "Select filter:" <<
        "\n0. Exit to menu" <<
        "\n1. By name" <<
        "\n2. By workshop for uncompleted pipes" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "Enter station name:" << endl;
        set<int> result = Search_By_Name(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).ShowInfo();

            cout << "Select all(0) or enter IDs (enter IDs for editing, to confirm changes enter 0)" << endl;
            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) stations.at(id).ShowInfo();

            cout << "Enter the percentage (0 - 10)" << endl;
            int answer = GetCorrectNumber(cin, 0, 10);
            if (numbers.empty())
            {
                for (auto& id : result) stations.at(id).Edit(answer);
            }
            else
            {
                for (auto& id : numbers) stations.at(id).Edit(answer);

            }
        }
        else cout << "No matching stations";
        break;
    }
    case 2:
    {
        ENTER;
        cout << "Enter workshop of stations:" << endl;
        set<int> result = Search_By_Workshop(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).ShowInfo();

            cout << "Select all(0) or enter IDs (enter IDs for editing, to confirm changes enter 0)" << endl;
            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) stations.at(id).ShowInfo();

            cout << "Enter the percentage (0 - 10)" << endl;
            int answer = GetCorrectNumber(cin, 0, 10);
            if (numbers.empty())
            {
                for (auto& id : result) stations.at(id).Edit(answer);
            }
            else
            {
                for (auto& id : numbers) stations.at(id).Edit(answer);

            }
        }
        else cout << "No matching stations";
        break;
    }
    case 0:
    {
        break;
    }
    }
}

//---------------Delete-------------------
void GTS::Delete()
{
    cout << "1. Delete pipe\n"
        << "2. Delete station\n"
        << "0. Exit" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        DeletePipes();
        break;
    }
    case 2:
    {
        DeleteStations();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::DeletePipes()
{
    if (!pipes.size())
    {
        cout << "No available pipes!\n" << endl;
        return;
    }

    cout << "1. Delete pipe by ID\n"
        << "2. Delete by filter\n"
        << "0. Exit" << endl;


    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "List of pipes:\n";
        ViewComponents(pipes);
        auto keys = GetKeys(pipes);
        cout << "Deleting pipes:";
        DeletePipes(keys);
        break;
    }
    case 2:
    {
        DeleteSomePipes();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::DeletePipes(std::vector<int>& ids)
{
    int number = GetCorrectNumber<int>(std::cin, 1, ids.size());
    pipes.erase(ids[number - 1]);
}

void GTS::DeleteStations()
{
    if (!pipes.size())
    {
        cout << "No available stations!\n" << endl;
        return;
    }

    cout << "1. Delete station by ID\n"
        << "2. Delete by filter\n"
        << "0. Exit" << endl;


    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "List of stations:\n";
        ViewComponents(stations);
        cout << "Deleting station : ";
        auto keys = GetKeys(stations);
        DeleteStations(keys);
        break;
    }
    case 2:
    {
        DeleteSomeStations();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::DeleteStations(std::vector<int>& ids)
{
    int number = GetCorrectNumber<int>(std::cin, 1, ids.size());
    stations.erase(ids[number - 1]);
}

void GTS::DeleteSomePipes()
{
    if (!pipes.size())
    {
        cout << "No available pipes!";
        return;
    }

    cout << "Select filter by:" <<
        "\n0. Exit to menu" <<
        "\n1. By name" <<
        "\n2. By status" << endl;;

    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "Enter the name of the pipe:" << endl;
        set<int> result = Search_By_Name(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).ShowInfo();

            cout << "Delete all (0) or enter IDs (enter IDs in order, for confirmation press Enter to delete 0)" << endl;
            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) pipes.at(id).ShowInfo();

            if (numbers.empty())
            {
                for (auto& id : result) pipes.erase(id);
            }
            else
            {
                for (auto& id : numbers) pipes.erase(id);
            }

            cout << "Pipes deleted!" << endl;
        }
        else cout << "No matching pipes found";
        break;
    }
    case 2:
    {
        ENTER;
        cout << "Enter the status of the pipes:" << endl;
        set<int> result = Search_By_Status(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).ShowInfo();

            cout << "Delete all (0) or enter IDs (enter IDs in order, for confirmation press Enter to delete 0)" << endl;
            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) pipes.at(id).ShowInfo();


            if (numbers.empty())
            {
                for (auto& id : result) pipes.erase(id);
            }
            else
            {
                for (auto& id : numbers) pipes.erase(id);
            }
            cout << "Pipes deleted!" << endl;
        }
        else cout << "No matching pipes found";
        break;
    }
    case 0:
    {
        break;
    }
    }
}
void GTS::DeleteSomeStations()
{
    if (!pipes.size())
    {
        cout << "No available pipes!";
        return;
    }

    cout << "Select filter by:" <<
        "\n0. Exit to menu" <<
        "\n1. By name" <<
        "\n2. By workshop" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "Enter the name of the station:" << endl;
        set<int> result = Search_By_Name(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).ShowInfo();

            cout << "Delete all (0) or enter the IDs to delete (enter IDs, to confirm delete enter 0)" << endl;

            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) stations.at(id).ShowInfo();

            if (numbers.empty())
            {
                for (auto& id : result) stations.erase(id);
            }
            else
            {
                for (auto& id : numbers) stations.erase(id);
            }
            cout << "Station(s) deleted!" << endl;
        }
        else cout << "No stations found";
        break;
    }
    case 2:
    {
        ENTER;
        cout << "Enter the workshop of uncompleted stations:" << endl;
        set<int> result = Search_By_Workshop(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).ShowInfo();

            cout << "Delete all (0) or enter the IDs to delete (enter IDs, to confirm delete enter 0)" << endl;
            set<int> numbers = GetEditNumbers(cin, result);

            ENTER;
            for (auto& id : numbers) stations.at(id).ShowInfo();

            if (numbers.empty())
            {
                for (auto& id : result) stations.erase(id);
            }
            else
            {
                for (auto& id : numbers) stations.erase(id);
            }
            cout << "Station(s) deleted!" << endl;
        }
        else cout << "No stations found";
        break;
    }
    case 0:
    {
        break;
    }
    }
}

//---------------Save - Load-------------------
void GTS::SaveConfiguration()
{
    if (pipes.size() or stations.size()) {
        cout << "Enter the file's name: " << endl;
        string name = input_string(cin);
        name = "Saves/" + name + ".txt";

        int MaxId_Pipe;
        int MaxId_Station;
        for (auto& pipe : pipes)
        {
            MaxId_Pipe = pipe.second.GetMaxId();
            break;
        }
        for (auto& station : stations)
        {
            MaxId_Station = station.second.GetMaxId();
            break;
        }

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << endl;
        for (auto& pipe : pipes)
            file << pipe.second;
        for (auto& station : stations)
            file << station.second;
        file.close();

        ENTER;
        cout << "Connection initialized successfully!" << endl;
    }

    else
    {
        ENTER; cout << "The connection could not be established, please check the data!" << endl;
    }
}

void GTS::LoadConfiguration() {
    ENTER;
    ifstream file;
    std::string path = "Saves\\";
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        cout << count << ". " << name << endl;
        //std::format(name);
    }

    ENTER;
    cout << "Connection reset" << endl;
    int save = GetCorrectNumber(cin, 1, count);

    count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        if (count == save) {
            pipes.clear();
            stations.clear();

            Pipe pipe;
            Station station;

            int count_pipes;
            int count_cs;

            file.open(name);
            file >> count_pipes >> count_cs;


            while (count_pipes--)
                // for (count_pipes; count_pipes > 0; count_pipes--)
            {
                file >> pipe;
                pipes.insert({ pipe.GetID(), pipe });
            }


            for (count_cs; count_cs > 0; count_cs--)
            {
                file >> station;
                stations.insert({ station.GetID(), station });
            }

            cout << "Files loaded!\n" << endl;
            break;
        }
    }
}