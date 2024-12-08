#include <filesystem>

#include "Utilites.h"
#include "GTS.h"

#define MIN_ID_PIPE  1
#define MIN_ID_STATION 1001

using namespace std;


//---------------Filter-------------------

template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repair) {
    return pipe.in_repair == in_repair;
}

bool CheckByDiameter(Pipe& pipe, int diameter) {
    return pipe.GetDiameter() == diameter;
}

bool CheckByWorkshop(Station& station, int cent_non_active) {
    return station.GetUnactiveWorkshop() >= cent_non_active;
}

template <typename Element, typename Parametr>
unordered_set<int> Find_By_Filter(unordered_map<int, Element>& elements, Filter<Element, Parametr> filter, Parametr parametr)
{
    unordered_set<int> result;
    for (auto& element : elements)
    {
        if (filter(element.second, parametr))
            result.insert(element.second.GetID());
    }
    return result;
}


//---------------Utils-------------------

GTS::GTS() {}

bool GTS::HasObject(const ObjectType obj)
{
    switch (obj)
    {
    case PIPE: {
        if (pipes.size()) { return true; }
        else { return false; }
    }
    case STATION: {
        if (stations.size()) { return true; }
        else { return false; }
    }
    default: { return false; }
    }
}

int GTS::InputExistIdStation() {
    int id;
    do {
        id = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());
        if (!stations.contains(id)) { cout << "There's no such station!" << endl; }
    } while (!stations.contains(id));
    return id;
}

unordered_set<int> GTS::GetIDs(const ObjectType obj)
{
    switch (obj) {
    case PIPE: { return GetKeys(pipes); }
    case STATION: { return GetKeys(stations); }
    default: { return unordered_set<int>{}; }
    }
}

unordered_set<int> GTS::GetEditNumbers(unordered_set<int>& result, const GTS::ObjectType obj)
{
    unordered_set<int> IDs;
    int id;
    int Max_ID;
    switch (obj) {
    case GTS::PIPE: { Max_ID = Pipe::GetMaxId(); break; }
    case GTS::STATION: { Max_ID = Station::GetMaxId(); break; }
    }
    id = GetCorrectNumber(0, Max_ID);
    if (id == 0) { return result; }
    else { IDs.insert(id); }
    do {
        id = GetCorrectNumber(0, Max_ID);
        if (result.contains(id)) {
            IDs.insert(id);
        }
    } while (id != 0);

    return IDs;
}

unordered_set<int> GTS::GetFreePipes(const unordered_set<int>& IDs) {
    unordered_set<int> free_IDs;
    for (auto& id : IDs) {
        if (!connections.edges.contains(id)) {
            free_IDs.insert(id);
        }
    }
    return free_IDs;
}


//---------------Creating-------------------
void GTS::CreatePipe() {
    Pipe pipe;
    pipe.WriteInfo();
    pipes.insert({ pipe.GetID(), pipe });
}

void GTS::CreateStateDiameterPipe(Pipe& pipe, int diameter) {
    pipe.WriteInfo_WithStateDiameter(diameter);
    pipes.insert({ pipe.GetID(), pipe });
}

void GTS::CreateCS()
{
    Station station;
    station.WriteInfo();
    stations.insert({ station.GetID(), station });
}


//---------------Show-------------------
void GTS::ViewPipes()
{
    int i = 1;
    for (auto& element : pipes) {
        std::cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }
}

void GTS::ViewStations()
{
    int i = 1;
    for (auto& element : stations) {
        std::cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }
}

void GTS::ViewObjects(unordered_set<int> result, const GTS::ObjectType obj)
{
    switch (obj) {
    case PIPE: { for (int id : result) { pipes.at(id).ShowInfo(); }; return; }
    case STATION: { for (int id : result) { stations.at(id).ShowInfo(); }; return; }
    default: { return; }
    }
}


//---------------Editing-------------------
void GTS::EditPipes(unordered_set<int>& IDs)
{
    ENTER;
    ViewObjects(IDs, PIPE);
    cout << "Change the state of the pipe(s)? (0 - under repair, 1 - operational, 2 - toggle state)" << endl;
    switch (GetCorrectNumber(0, 2))
    {
    case 0: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_REPAIR); }      break; }
    case 1: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_WORK); }        break; }
    case 2: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_OPPOSITE); }  break; }
    default: { return; }
    }
    cout << endl << "State has been changed!" << endl;
}

void GTS::EditStations(unordered_set<int>& IDs)
{
    ENTER;
    ViewObjects(IDs, STATION);
    cout << "Change the number of active workshops in the station(s) to (0-10): " << endl;
    int ans = GetCorrectNumber(0, 10);
    for (int id : IDs) { stations.at(id).Edit(ans); }
    cout << endl << "Has been changed!" << endl;
}

void GTS::Edit_ByName(const ObjectType obj)
{
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Enter the name of the pipe:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "Edit all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            EditPipes(numbers);
        }
        else cout << "No matching pipes";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Enter the name of the station:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "Edit all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            EditStations(numbers);
        }
        else cout << "No matching stations";
        break;
    }
    default: { return; }
    }

}

void GTS::Edit_ByParametr(const ObjectType obj) {
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Enter the state of the pipe: (0 - under repair, 1 - operational)" << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "Edit all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            EditPipes(numbers);
        }
        else cout << "No matching pipes";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Enter the percentage of inactive workshops in the station:" << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "Edit all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            EditStations(numbers);
        }
        else cout << "No matching stations";
        break;
    }
    default: { return; }
    }
}

//---------------Deleting-------------------
void GTS::DeletePipes(unordered_set<int>& IDs) {
    for (auto& id : IDs) pipes.erase(id);
    cout << endl << "Pipes have been deleted!" << endl;
}
void GTS::DeleteStations(unordered_set<int>& IDs) {
    for (auto& id : IDs) stations.erase(id);
    cout << endl << "Stations have been deleted!" << endl;
}

void GTS::Delete_ByName(const ObjectType obj)
{
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Enter the name of the pipe : " << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "Delete all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            DeletePipes(numbers);
        }
        else cout << "No matching pipes";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Enter the name of the station:" << endl;

        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "Delete all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            DeleteStations(numbers);
        }
        else cout << "No matching stations";
        break;
    }
    default: { return; }
    }

}

void GTS::Delete_ByParametr(const ObjectType obj) {
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Enter the state of the pipe: (0 - under repair, 1 - operational)" << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "Delete all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            DeletePipes(numbers);
        }
        else cout << "No matching pipes";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Enter the percentage of inactive workshops in the station:" << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "Delete all (0) or Enter specific IDs (Enter IDs one by one, and enter 0 to finish selection)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            DeleteStations(numbers);
        }
        else cout << "No matching stations";
        break;
    }
    default: { return; }
    }
}

//---------------Graph-------------------

void GTS::ViewConnections() {
    ENTER;
    connections.ViewConnections();
}

void GTS::CreateConnection() {
    if (stations.size() < 2) { cout << "Not enough stations to create a connection!" << endl; return;}
    ViewStations();
    cout << "Enter the ID of the starting station" << endl;
    int from, to, id;
    from = InputExistIdStation();
    cout << "Enter the ID of the ending station" << endl;
    to = InputExistIdStation();

    if (connections.UncorrectNodes(from, to)) { return; }

    cout << "Enter the pipe diameter you want to use to connect the stations:" << endl;
    vector<int> sizes = Pipe::GetSizes();
    int diameter = SwitchNumber(sizes);
    unordered_set<int> result = Find_By_Filter<Pipe, int>(pipes, CheckByDiameter, diameter);
    result = GetFreePipes(result);

    if (!result.size()) {
        cout << "No pipes with the specified diameter found. Do you want to create such a pipe? (0 - No (exit), 1 - Yes)" << endl;
        if (!GetCorrectNumber(0, 1)) { return; }
        else {
            Pipe pipe;
            CreateStateDiameterPipe(pipe, diameter);
            id = pipe.GetID();
            connections.CreateConnection(from, to, id);
            return;
        }
    }

    ViewObjects(result, PIPE);
    cout << "Select the ID of the pipe for the connection:";
    do {
        id = GetCorrectNumber(MIN_ID_PIPE, Pipe::GetMaxId());
        if (!result.contains(id)) { cout << "There is no such ID among the found pipes! Please enter it again." << endl;}
    } while (!result.contains(id));

    connections.CreateConnection(from, to, id);
    return;
}

void GTS::DeleteConnection() {
    if (connections.Empty()) { cout << "No available connections!"; return;}
    connections.ViewConnections();
    cout << "Enter the ID of the connection to be removed:" << endl;
    int id;
    do {
        id = GetCorrectNumber(MIN_ID_PIPE, Pipe::GetMaxId());
        if (!connections.edges.contains(id)) { cout << "There is no such ID among the found pipes! Please enter it again." << endl;}
    } while (!connections.edges.contains(id));
    connections.DeleteConnection(id);
}

void GTS::TopologicalSort() {
    Graph graph = Graph(connections.edges, connections.nodes, pipes);
    vector<int> result = graph.TopologicalSort();
    if (!result.size()) { cout << "Topological sorting: "; return; }
    cout << "Topological sorting: ";
    for (auto& i : result) {
        cout << i << " ";
    }
}


void GTS::ShortestPath() {
    Graph graph = Graph(connections.edges, connections.nodes, pipes);
    cout << "Enter the starting vertex of the path:" << endl;
    int StartNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    cout << "Enter the ending vertex of the path:" << endl;
    int EndNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    vector<int> result = graph.Metod_Deikstra(StartNode, EndNode);
    if (!result.size()) { cout << "Result: - "; return; }
    cout << "Result: ";
    for (auto& i : result) {
        cout << i << " -> ";
    }
    cout << "end" << endl;
}
//---------------—--Save/Load-----------------
void GTS::SaveConfiguration()
{
    if (HasObject(PIPE) or HasObject(STATION)) {
        cout << "Enter name of the file :" << endl;
        string name = input_string();
        name = "Saves/" + name + ".txt";

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << " " << connections.edges.size() << endl;
        for (auto& pipe : pipes) { file << pipe.second; }
        for (auto& station : stations) { file << station.second; };
        file << connections;
        file.close();
        ENTER;
        cout << "Saved succesfully!" << endl;
    }
    else { ENTER; cout << "The storage cannot be empty, please enter the data!" << endl;}
}

void GTS::LoadConfiguration() {
    ENTER;
    ifstream file;
    std::string path = "Saves\\";
    vector<std::filesystem::directory_entry> names;
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        names.push_back(name);
        cout << count << ". " << name << endl;
    }

    ENTER;
    cout << "Enter number of saving" << endl;
    int save = GetCorrectNumber(1, count);

    pipes.clear();
    stations.clear();
    connections.Clear();
    Pipe pipe;
    Station station;
    Edge edge;
    int count_pipes, count_cs, count_connectios;

    file.open(names[save-1]);
    file >> count_pipes >> count_cs >> count_connectios;

    while (count_pipes--)
    {
        file >> pipe;
        pipes.insert({ pipe.GetID(), pipe });
    }
    while (count_cs--)
    {
        file >> station;
        stations.insert({ station.GetID(), station });
    }
    while (count_connectios--)
    {
        file >> edge;
        connections.edges.insert({ edge.pipe, edge });
        connections.nodes.insert({ edge.from });
        connections.nodes.insert({ edge.to });
    }

    cout << "Files loaded!\n" << endl;
    file.close();
}
