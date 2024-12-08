#include "Connections.h"

using namespace std;

bool Connections::Empty()
{
    if (edges.size()) { return true; }
    else { return false; }
}

bool Connections::UncorrectNodes(int from, int to)
{
    if (nodes.contains(from) && nodes.contains(to)) {
        cout << "Stations are already in use!" << endl; return true;
    }
    else if (from == to) {
        cout << "Cannot create a connection to the same station!" << endl; return true;
    }
    else { return false; }
}

void Connections::CreateConnection(int from, int to, int id) {
    if (UncorrectNodes(from, to)) { return; }
    if (edges.contains(id)) {
        cout << "Stations or pipe are already in use!" << endl; return;
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

void Connections::DeleteConnection(int id) {
    if (edges.contains(id)) {
        Edge edge = edges.at(id);
        ResetNodes();
        edges.erase(id);
        cout << endl << "Connection deleted!" << endl;
    }
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