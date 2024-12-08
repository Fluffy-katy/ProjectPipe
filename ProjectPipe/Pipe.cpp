#include "Pipe.h"

using namespace std;

int Pipe::MaxId = 0;

vector<int> Pipe::possible_diameters = { 500, 700, 1000, 1400 };


//  Constructor pipe
Pipe::Pipe()
{
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repair = 0;
    ID = ++MaxId;
}

//  Constructor loading pipe
Pipe::Pipe(string name, float length, int diameter, bool in_repair) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_repair = in_repair;
}

// Write Info pipe
void Pipe::WriteInfo() {
    ENTER;
    cout << "Enter pipe's name:" << endl;
    name = input_string();


    cout << "Enter pipe's lenth(m):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    cout << "Enter pipe's diameter(m):" << endl;
    diameter = SwitchNumber(possible_diameters);

    cout << "Enter pipe's state:(0 - in repair; 1 - working)" << endl;

    if (GetCorrectNumber(0, 1)) { in_repair = true; }
    else { in_repair = false; }
}

void Pipe::WriteInfo_WithStateDiameter(int diameter) {
    ENTER;
    cout << "Enter pipe's name:" << endl;
    name = input_string();


    cout << "Enter pipe's lenth(m):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    this->diameter = diameter;

    cout << "Enter pipe's state:(0 - in repair; 1 - working)" << endl;

    if (GetCorrectNumber(0, 1)) { in_repair = true; }
    else { in_repair = false; }
}

// Show info
void Pipe::ShowInfo() {
    string status = in_repair ? " working " : " in repair";
    cout << "Pipe " << name << "; length: " << length << "; diameter: " << diameter
        << "; Status:" << status << "; Id: " << ID << endl;
}



void Pipe::Edit(const Action act) {
    switch (act) {
    case SET_WORK: { in_repair = true; return; }
    case SET_REPAIR: { in_repair = false; return; }
    case SET_OPPOSITE: { in_repair = !in_repair; return; }
    default: { return; }
    }
}

ofstream& operator << (ofstream& file, const Pipe& pipe) {
    if (file.is_open()) {
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.in_repair << endl;
        file << pipe.ID << endl;
    }
    return file;
}


ifstream& operator >> (ifstream& file, Pipe& pipe) {
    if (file.is_open()) {
        file >> ws;
        getline(file, pipe.name);
        file >> pipe.length;
        file >> pipe.diameter;
        file >> pipe.in_repair;
        file >> pipe.ID;
        Pipe::MaxId = (Pipe::MaxId < pipe.ID) ? pipe.ID : Pipe::MaxId;
    }
    return file;
}

