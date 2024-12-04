#pragma once

#include "Utilites.h"


class Pipe
{
    float length;
    int diameter;
    int ID;
    static int MaxId;


public:

    std::string name;
    bool in_repair;

    Pipe();
    Pipe(const std::string name, const float length, const int diameter, const bool in_repair);

    void WriteInfo();

    void ShowInfo();

    void Edit();

    void Edit(int status);

    static int GetMaxId() { return MaxId; };

    int GetID() { return ID; };


    friend std::ofstream& operator << (std::ofstream& out, const Pipe& pipe);
    friend std::ifstream& operator >> (std::ifstream& file, Pipe& pipe);
};