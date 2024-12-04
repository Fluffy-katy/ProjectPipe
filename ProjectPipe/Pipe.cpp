#include "Pipe.h"

using namespace std;

int Pipe::MaxId = 0;

// Constructor pipe
Pipe::Pipe()
{
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repair = 0;
    ID = ++MaxId;
}

// Constructor loading pipe
Pipe::Pipe(string name, float length, int diameter, bool in_repair) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_repair = in_repair;
}

// Show Info pipe
void Pipe::WriteInfo() {
    ENTER;
    cout << "Enter pipe's name:" << endl;
    name = input_string(cin);


    cout << "Enter pipe's lenth(m):" << endl;
    length = GetCorrectNumber(cin, 1.0, 100000000.);

    cout << "Enter pipe's diameter(m):" << endl;
    diameter = GetCorrectNumber(cin, 100, 1400);

    cout << "Enter pipe's state:(0 - in repair; 1 - working)" << endl;
    if (cin, GetCorrectNumber(cin, 0, 1)) {
        in_repair = true;
    }
    else {
        in_repair = false;
    }
}

// info
void Pipe::ShowInfo() {
    string sostoyanie = in_repair ? " working " : " in repair";
    cout << "Pipe " << name << "; Lenght: " << length << "; Diameter: " << diameter
        << "; State:" << sostoyanie << "; Id: " << ID << endl;
}


void Pipe::Edit(int status) {
    if (status) in_repair = !in_repair;
}


void Pipe::Edit()
{
    ENTER;
    ShowInfo();
    cout << "Change state of pipe?(0 - no, 1 - yes)" << endl;
    Edit(GetCorrectNumber(cin, 0, 1));
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

