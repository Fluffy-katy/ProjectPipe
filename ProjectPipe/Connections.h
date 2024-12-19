#pragma once
#include "Graph.h"




class Connections {
public:
    std::unordered_map<int, Edge> edges;
    std::set<int> nodes;

    bool Empty();

    void Clear() { edges.clear(); }

    bool UncorrectNodes(int from, int to);

    void Insert(Edge& edge);

    void CreateConnection(int from, int to, int id);

    void ViewConnections();

    void DeleteConnection_ByPipeID(int id);

    void DeleteConnection_ByStationID(int id);

    friend std::ofstream& operator << (std::ofstream& file, const Connections& connections);
private:
    void ResetNodes();
};