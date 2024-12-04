#pragma once

#include "Utilites.h"
#include "Pipe.h"
#include "Station.h"


class GTS
{

    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Station> stations;


public:

    GTS();
    //---------------Add obj-------------------
    void CreatePipe();
    void CreateCS();

    //---------------Show obj-------------------
    void View();

    template <typename Struct>
    void ViewComponents(std::unordered_map<int, Struct>& conteiner)
    {
        int i = 1;
        for (auto& element : conteiner) {
            std::cout << i << ". ";
            i++;
            element.second.ShowInfo();
        }
    }

    template <typename Struct>
    void ViewComponentsByID(std::set<int> IDs, std::unordered_map<int, Struct>& conteiner)
    {
        int i = 1;
        for (auto& id : IDs) {
            std::cout << i << ". ";
            i++;
            conteiner.at(id).ShowInfo();
        }
    }


    //--------------Search-------------------
    void Search();
    void SearchPipes();
    void SearchCS();

    //---------------Edd-------------------
    void Edit();

    void EditPipes();
    void EditCS();

    void EditOnePipe();
    void EditOneCS();
    void EditSomePipes();
    void EditSomeCS();

    template <typename Struct>
    void EditOne(std::unordered_map<int, Struct>& structure)
    {
        auto keys = GetKeys(structure);
        int number = GetCorrectNumber<int>(std::cin, 1, keys.size()) - 1;
        structure[keys[number]].Edit();
    }



    //---------------Del-------------------
    void Delete();
    void DeletePipes();
    void DeleteStations();


    void DeletePipes(std::vector<int>& ids);
    void DeleteStations(std::vector<int>& ids);

    void DeleteSomePipes();
    void DeleteSomeStations();

    //---------------Save-Load-------------------
    void SaveConfiguration();
    void LoadConfiguration();

};