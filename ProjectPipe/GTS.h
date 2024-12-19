#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include "Connections.h"
#include "Graph.h"

class GTS
{
public:
    enum ObjectType { PIPE, STATION };
    bool HasObject(const ObjectType obj);
    std::unordered_set<int> GetIDs(const ObjectType obj);
    GTS();

    //---------------—Creating objects----------------
    void CreatePipe();
    void CreateStateDiameterPipe(Pipe& pipe, int diameter);
    void CreateCS();

    //---------------Show objects-------------------
    void ViewPipes();
    void ViewStations();

    //---------------Edit-------------------
    void EditPipes(std::unordered_set<int>& IDs);
    void EditStations(std::unordered_set<int>& IDs);

    void Edit_ByName(const ObjectType obj);
    void Edit_ByParametr(const ObjectType obj);

    //---------------Deliting-------------------
    void DeletePipes(std::unordered_set<int>& IDs);
    void DeleteStations(std::unordered_set<int>& IDs);

    void Delete_ByName(const ObjectType obj);
    void Delete_ByParametr(const ObjectType obj);

    //---------------Graph-------------------
    void ViewConnections();
    void CreateConnection();
    void DeleteConnection();
    void TopologicalSort();
    void ShortestPath();
    void MaxFlow();

    //---------------Save/Load-------------------
    void SaveConfiguration();
    void LoadConfiguration();


private:
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Station> stations;
    Connections connections;

    int InputExistIdStation();
    std::unordered_set<int> GetFreePipes(const std::unordered_set<int>& IDs);
    std::unordered_set<int> GetEditNumbers(std::unordered_set<int>& result, const GTS::ObjectType obj);
    void ViewObjects(std::unordered_set<int> result, const GTS::ObjectType obj);
};