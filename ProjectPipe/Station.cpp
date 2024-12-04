#include "Station.h"

using namespace std;


// Construktor CS
Station::Station() {
    name = "Non";
    number_of_workshops = 0;
    active_workshops = 0;
    efficianty = 0;
    ID = ++MaxId;
}

// Construktor CS for loading
Station::Station(string name, int number_of_workshops, int active_workshops, int efficianty) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->efficianty = efficianty;
}

// Info CS
void Station::WriteInfo() {
    ENTER;

    cout << "Enter CS's name:" << endl;
    name = input_string(cin);

    cout << "Enter number of workshops:" << endl;
    number_of_workshops = GetCorrectNumber(cin, 0, 10);

    cout << "Enter number of active workshops:" << endl;
    active_workshops = GetCorrectNumber(cin, 0, number_of_workshops);

    cout << "Efficiancy level(0-100)" << endl;
    efficianty = GetCorrectNumber(cin, 0, 100);

}

// Print constructor CS
void Station::ShowInfo() {

    cout << "CS " << name << "; Number of workshops: " << number_of_workshops << "; Active workshops: "
        << active_workshops << "; Efficianty: " << efficianty << "; Id: " << ID << endl;
}


void Station::Edit(int active) {
    active_workshops = active;
    if (active_workshops > number_of_workshops)
    {
        active_workshops = number_of_workshops;
    }
}


// Constructor of CS
void Station::Edit()
{
    ENTER;
    ShowInfo();
    cout << "Enter number of workshops:" << endl;
    int answer = GetCorrectNumber(cin, 0, number_of_workshops);
    Edit(answer);
}

ofstream& operator << (ofstream& file, const Station& CS) {
    if (file.is_open()) {
        file << CS.name << endl;
        file << CS.number_of_workshops << endl;
        file << CS.active_workshops << endl;
        file << CS.efficianty << endl;
        file << CS.ID << endl;
    }
    return file;
}


ifstream& operator >> (ifstream& file, Station& CS) {
    if (file.is_open()) {
        file >> ws;
        getline(file, CS.name);
        file >> CS.number_of_workshops;
        file >> CS.active_workshops;
        file >> CS.efficianty;
        file >> CS.ID;
        if (CS.ID > Station::MaxId)
            Station::MaxId = CS.ID;
    }
    return file;
}