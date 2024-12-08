#include "Station.h"

using namespace std;


// CS constructor
Station::Station() {
    name = "Non";
    number_of_workshops = 0;
    active_workshops = 0;
    efficianty = 0;
    ID = ++MaxId;
}

// CS constructor loading
Station::Station(string name, int number_of_workshops, int active_workshops, int efficianty) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->efficianty = efficianty;
}

// Show
void Station::WriteInfo() {
    ENTER;

    cout << "Enter the name of the CS:" << endl;
    name = input_string();

    cout << "Enter the number of workshops:" << endl;
    number_of_workshops = GetCorrectNumber(0, 10);

    cout << "Enter the number of active workshops" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);

    cout << "Enter the efficiency of the station (0-100)" << endl;
    efficianty = GetCorrectNumber(0, 100);

}

// ѕросмотр информации  —
void Station::ShowInfo() {
   
    cout << "CS " << name << "; Number of workshops: " << number_of_workshops << "; Active workshops: "
        << active_workshops << "; efficiency: " << efficianty << "; Id:" << ID << endl;
}


void Station::Edit(int active) {
    active_workshops = active;
    if (active_workshops > number_of_workshops)
    {
        active_workshops = number_of_workshops;
    }
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

