#include "Connections.h"

using namespace std;

bool Connections::Empty()
{
    if (edges.size()) { return false; }
    else { return true; }
}

void Connections::Insert(Edge& edge) {
    edges.insert({ edge.pipe, edge });
    nodes.insert({ edge.from });
    nodes.insert({ edge.to });
}

bool Connections::UncorrectNodes(int from, int to)
{
    if (from == to) {
        cout << "It's not possible connect the same station!" << endl; return true;
    }
    else { return false; }
}

void Connections::CreateConnection(int from, int to, int id) {
    if (UncorrectNodes(from, to)) { return; }
    if (edges.contains(id)) {
        cout << "The station or pipe is already in use!" << endl; return;
    }
    Edge edge = Edge(from, to, id);
    edges.insert({ id, edge });
    nodes.insert(from);
    nodes.insert(to);
    cout << endl << "Connection created!" << endl;
    return;
}

void Connections::ViewConnections()
{
    if (edges.empty()) { cout << "No connections!" << endl; }
    for (auto& edge : edges) {
        cout << "Connection: Pipe " << edge.second.pipe << " connects stations "
            << edge.second.from << " -> " << edge.second.to << endl;
    }
}

void Connections::DeleteConnection_ByPipeID(int pipe_id) {
    if (edges.contains(pipe_id)) {
        edges.erase(pipe_id);
        cout << "Connection " << pipe_id << " delited\n";
        ResetNodes();
    }
}

void Connections::DeleteConnection_ByStationID(int station_id) {
    vector<int> ID_edges;
    for (auto& [pipe_id, edge] : edges) {
        if (edge.from == station_id || edge.to == station_id) { ID_edges.push_back(pipe_id); }
    }

    for (int id : ID_edges) {
        edges.erase(id);
        cout << "Connection " << id << " delited\n";
    }
    ResetNodes();
}

void Connections::ResetNodes()
{
    nodes.clear();
    for (auto& edge : edges) {
        nodes.insert(edge.second.from);
        nodes.insert(edge.second.to);
    }
}



ofstream& operator << (ofstream& file, const Connections& connections) {
    if (file.is_open()) {
        for (auto& edge : connections.edges) { file << edge.second; }
    }
    return file;
}