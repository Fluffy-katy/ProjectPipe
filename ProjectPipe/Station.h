#pragma once

#include "Utilites.h"


class Station {
    int number_of_workshops;
    int efficianty;
    int ID;
    inline static int MaxId = 1000;

public:

    std::string name;
    int active_workshops;

    Station();
    Station(std::string name, int number_of_workshops, int active_workshops, int efficianty);

    void WriteInfo();

    void ShowInfo();

    void Edit(int active);

    static int GetMaxId() { return MaxId; };
    double GetUnactiveWorkshop() { return (1.0 - (double)active_workshops / (double)number_of_workshops) * 100.0; }

    int GetID() { return ID; };

    friend std::ofstream& operator << (std::ofstream& out, const Station& CS);
    friend std::ifstream& operator >> (std::ifstream& file, Station& CS);
};