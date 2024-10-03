#include <iostream>
#include <fstream>
#include <string>
using namespace std;

 
void BuffCleaner() {
    cout << "Invalid input\n";
    cin.clear();
    cin.ignore(10000, '\n');
}

struct Pipe {
    string name = "None";
    int length = 0;
    int diameter = 0;
    bool in_repair = false;
};

struct CStation {
    string name = "None";
    int number_of_workshops = 0;
    int active_workshops = 0;
    int productivity = 0;
};

void PrintMenu() {
    cout << "1. Input pipe\n"
        << "2. Input cs's\n"
        << "3. Show information\n"
        << "4. Change pipe repair state\n"
        << "5. Edit number of active workshops\n"
        << "6. Save data\n"
        << "7. Load data from file\n"
        << "0. Exit\n"
        << "Select an option: ";
}

//Pipe
Pipe InputPipe() { 
    Pipe p;
    cout << "Enter pipe name: ";
    cin >> ws; 
    getline(cin, p.name);

    cout << "Enter length: ";
    while (!(cin >> p.length) || p.length <= 0) {
        BuffCleaner();
        cout << "Enter length: ";
    }

    cout << "Enter diameter: ";
    while (!(cin >> p.diameter) || p.diameter <= 0) {
        BuffCleaner();
        cout << "Enter diameter: ";
    }

    cout << "Pipe's repair state: (1 - working, 0 - in repair): ";
    while (!(cin >> p.in_repair)) {
        BuffCleaner();
        cout << "Pipe's repair state: (1 - working, 0 - in repair): ";
    }
    cout << "\n";
    return p;
}

void PrintPipeInfo(const Pipe& p) {
    cout << "Pipe name: " << p.name << endl;
    cout << "Pipe length: " << p.length << endl;
    cout << "Pipe diameter: " << p.diameter << endl;
    cout << "State: " << (p.in_repair ? "Under repair\n" : "Working\n");
    cout << "\n";
}

void SwitchRepairState(Pipe& p) {
    p.in_repair = !p.in_repair;
    cout << "Pipe repair state successfully changed\n\n";
}
//CS
CStation InputCStation() {
    CStation cs;

    cout << "Enter compressor station name: ";

    getline(cin >> ws, cs.name);

    cout << "Enter total number of workshops: ";
    while (!(cin >> cs.number_of_workshops) || cs.number_of_workshops <= 0) {
        BuffCleaner();
        cout << "Enter total number of workshops: ";
    }

    cout << "Enter number of active workshops: ";
    while (!(cin >> cs.active_workshops) || cs.active_workshops < 0 || cs.active_workshops > cs.number_of_workshops) {
        BuffCleaner();
        cout << "Enter number of active workshops: ";
    }

    cout << "Enter productivity level (0-100%): ";
    while (!(cin >> cs.productivity) || cs.productivity < 0 || cs.productivity > 100) {
        BuffCleaner();
        cout << "Enter productivity level (0-100%): ";
    }
    cout << "\n";
    return cs;
}

void PrintCStationInfo(const CStation& cs) {
    cout << "CS's name: " << cs.name << endl;
    cout << "Number of workshops: " << cs.number_of_workshops << endl;
    cout << "Active workshops: " << cs.active_workshops << endl;
    cout << "Productivity: " << cs.productivity << "%" << endl;
    cout << "\n";
}

void EditCStationWorkshops(CStation& cs) {
    int workshopChange;
    cout << "Enter change in operating workshops (- or +): "<< "" << cs.active_workshops << endl;
    while (!(cin >> workshopChange) || (cs.active_workshops +  workshopChange) > cs.number_of_workshops
        || (cs.active_workshops + workshopChange) < 0 || workshopChange == 0) {
        BuffCleaner();
        cout << "Enter valid change: It should be less than number of ws";
    }
    cs.active_workshops += workshopChange;
    cout << "Number of active workshops is updated\n\n";
}

//save load
void SavePipe(ofstream& fout, const Pipe& p) {
    string Marker = "pipe";
    if (p.name == "None") fout << Marker << endl;
    else
    {
        fout << p.name << endl;
        fout << p.length << endl;
        fout << p.diameter << endl;
        fout << p.in_repair << endl;
    }
}

void SaveCS(ofstream& fout, const CStation& cs) {
    string Marker = "CS";
    if (cs.name == "None") fout << Marker << endl;
    else
    {
        fout << cs.name << endl;
        fout << cs.number_of_workshops << endl;
        fout << cs.active_workshops << endl;
        fout << cs.productivity << endl;
    }
}

Pipe LoadPipe(ifstream& fin) {
    Pipe p;
    string Marker;
    getline(fin >> ws, Marker);
    if (Marker == "pipe") return p = { "None", 0, 0, 0 };
    else {
        p.name = Marker;
        fin >> p.length;
        fin >> p.diameter;
        fin >> p.in_repair;
        return p;

    }

}

CStation LoadCS(ifstream& fin) {
    string Marker;
    CStation cs;
    getline(fin >> ws, Marker);
    if (Marker == "CS") return cs = { "None", 0, 0, 0 };
    else {
        cs.name = Marker;
        fin >> cs.number_of_workshops;
        fin >> cs.active_workshops;
        fin >> cs.productivity;
        return cs;

    }
}



int main() {
    Pipe p;
    CStation cs;

    cout << "Hello, world!\n\n" << endl;

    while (true) {
        PrintMenu();
        int digit;
        while (!(cin >> digit)) {
            BuffCleaner();
            PrintMenu();
        }


        switch (digit) {
        case 1: 
            p = InputPipe();
            break;

        case 2:
            cs = InputCStation();
            break;

        case 3:
            if (p.name == "None") {
                cout << "No pipe data available\n\n";
            }
            else {
                PrintPipeInfo(p);
            }
            if (cs.name == "None") {
                cout << "No compressor station data available\n\n";
            }
            else {
                PrintCStationInfo(cs);
            }
            break;

        case 4:
            if (p.name != "None") {
                SwitchRepairState(p);
            }
            else {
                cout << "No pipe data available\n\n";
            }
            break;

        case 5:
            if (cs.name != "None") {
                EditCStationWorkshops(cs);
            }
            else {
                cout << "No CS's data available\n\n";
            }
            break;

        case 6: {
            ofstream fout;
            fout.open("data.txt", ios::out);
            if (fout.is_open()) {
                SavePipe(fout, p);
                SaveCS(fout, cs);
                fout.close();
                cout << "Data is saved\n\n";
            }
            else {

                cout << "File didn't open\n\n";
            }
            break;
        }

        case 7: {
            ifstream fin;
            fin.open("data.txt", ios::in);
            if (fin.is_open()) {
                p = LoadPipe(fin);
                cs = LoadCS(fin);
                fin.close();
                cout << "Data successfully loaded\n\n";
            }
            else {
                cout << "Error opening file for reading\n\n";
            }
            break;
        }

        case 0:
            return 0;

        default:
            cout << "Wrong selection\n\n";
            break;
        }
    }
    return 0;
}
