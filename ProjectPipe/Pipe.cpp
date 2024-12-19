#include "Pipe.h"
#include <math.h>

using namespace std;

int Pipe::MaxId = 0;

vector<int> Pipe::possible_diameters = { 500, 700, 1000, 1400 };


//  Constructor pipe
Pipe::Pipe()
{
    name = "Non";
    length = 0.0;
    diameter = 0;
    //in_repair = 0;
    in_work = 0;
    ID = ++MaxId;
}

//  Constructor loading pipe
Pipe::Pipe(string name, float length, int diameter, bool in_work) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_work = in_work;
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

    if (GetCorrectNumber(0, 1)) { in_work = true; }
    else { in_work = false; }
}

void Pipe::WriteInfo_WithStateDiameter(int diameter) {
    ENTER;
    cout << "Enter pipe's name:" << endl;
    name = input_string();


    cout << "Enter pipe's lenth(m):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    this->diameter = diameter;

    cout << "Enter pipe's state:(0 - in repair; 1 - working)" << endl;

    if (GetCorrectNumber(0, 1)) { in_work = true; }
    else { in_work = false; }
}

// Show info
void Pipe::ShowInfo() {
    string status = in_work ? " working " : " in repair";
    cout << "Pipe " << name << "; length: " << length << "; diameter: " << diameter
        << "; Status:" << status << "; Id: " << ID << endl;
}



void Pipe::Edit(const Action act) {
    switch (act) {
    case SET_WORK: { in_work = true; return; }
    case SET_REPAIR: { in_work = false; return; }
    case SET_OPPOSITE: { in_work = !in_work; return; }
    default: { return; }
    }
}

double Pipe::GetCapacity() const {
    double capacity = sqrt(pow(diameter, 5) / length);
    return in_work ? capacity : -DBL_MAX;
}

ofstream& operator << (ofstream& file, const Pipe& pipe) {
    if (file.is_open()) {
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.in_work << endl;
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
        file >> pipe.in_work;
        file >> pipe.ID;
        Pipe::MaxId = (Pipe::MaxId < pipe.ID) ? pipe.ID : Pipe::MaxId;
    }
    return file;
}

