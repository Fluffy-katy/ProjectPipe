#include <iostream>
#include <fstream>
#include <string>
using namespace std;

 
void ClearCinBuffer() {
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

struct CompressorStation {
    string name = "None";
    int number_of_workshops = 0;
    int active_workshops = 0;
    int efficiency = 0;
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

    cout << "Enter pipe length: ";
    while (!(cin >> p.length) || p.length <= 0) {
        ClearCinBuffer();
        cout << "Enter pipe length: ";
    }

    cout << "Enter pipe diameter: ";
    while (!(cin >> p.diameter) || p.diameter <= 0) {
        ClearCinBuffer();
        cout << "Enter pipe diameter: ";
    }

    cout << "Is the pipe under repair? (1 - Yes, 0 - No): ";
    while (!(cin >> p.in_repair)) {
        ClearCinBuffer();
        cout << "Is the pipe under repair? (1 - Yes, 0 - No): ";
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

void TogglePipeRepairState(Pipe& p) {
    p.in_repair = !p.in_repair;
    cout << "Pipe repair state successfully changed\n\n";
}
//CS
CompressorStation InputCompressorStation() {
    CompressorStation cs;

    cout << "Enter compressor station name: ";

    getline(cin >> ws, cs.name);

    cout << "Enter total number of workshops: ";
    while (!(cin >> cs.number_of_workshops) || cs.number_of_workshops <= 0) {
        ClearCinBuffer();
        cout << "Enter total number of workshops: ";
    }

    cout << "Enter number of operating workshops: ";
    while (!(cin >> cs.active_workshops) || cs.active_workshops < 0 || cs.active_workshops > cs.number_of_workshops) {
        ClearCinBuffer();
        cout << "Enter number of operating workshops: ";
    }

    cout << "Enter efficiency level (0-100): ";
    while (!(cin >> cs.efficiency) || cs.efficiency < 0 || cs.efficiency > 100) {
        ClearCinBuffer();
        cout << "Enter efficiency level (0-100): ";
    }
    cout << "\n";
    return cs;
}

void PrintCompressorStationInfo(const CompressorStation& cs) {
    cout << "Compressor station name: " << cs.name << endl;
    cout << "Total number of workshops: " << cs.number_of_workshops << endl;
    cout << "Operating workshops: " << cs.active_workshops << endl;
    cout << "Efficiency: " << cs.efficiency << "%" << endl;
    cout << "\n";
}

void EditCompressorStationWorkshops(CompressorStation& cs) {
    int workshopChange;
    cout << "Enter change in operating workshops (positive or negative number): ";
    while (!(cin >> workshopChange) || (cs.active_workshops + workshopChange) > cs.number_of_workshops
        || (cs.active_workshops + workshopChange) < 0 || workshopChange == 0) {
        ClearCinBuffer();
        cout << "Enter valid change: ";
    }
    cs.active_workshops += workshopChange;
    cout << "Number of operating workshops successfully updated\n\n";
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

void SaveCS(ofstream& fout, const CompressorStation& cs) {
    string Marker = "CS";
    if (cs.name == "None") fout << Marker << endl;
    else
    {
        fout << cs.name << endl;
        fout << cs.number_of_workshops << endl;
        fout << cs.active_workshops << endl;
        fout << cs.efficiency << endl;
    }
}

Pipe LoadPipe(ifstream& fin, Pipe& p) {
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

CompressorStation LoadCS(ifstream& fin, CompressorStation& cs) {
    string Marker;
    getline(fin >> ws, Marker);
    if (Marker == "CS") return cs = { "None", 0, 0, 0 };
    else {
        cs.name = Marker;
        fin >> cs.number_of_workshops;
        fin >> cs.active_workshops;
        fin >> cs.efficiency;
        return cs;

    }
}



int main() {
    Pipe p;
    CompressorStation cs;

    while (true) {
        PrintMenu();
        int selection;
        while (!(cin >> selection)) {
            ClearCinBuffer();
            PrintMenu();
        }


        switch (selection) {
        case 1: 
            p = InputPipe();
            break;

        case 2:
            cs = InputCompressorStation();
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
                PrintCompressorStationInfo(cs);
            }
            break;

        case 4:
            if (p.name != "None") {
                TogglePipeRepairState(p);
            }
            else {
                cout << "No pipe data available\n\n";
            }
            break;

        case 5:
            if (cs.name != "None") {
                EditCompressorStationWorkshops(cs);
            }
            else {
                cout << "No compressor station data available\n\n";
            }
            break;

        case 6: {
            ofstream fout("data.txt");
            if (fout.is_open()) {
                SavePipe(fout, p);
                SaveCS(fout, cs);
                fout.close();
                cout << "Data successfully saved\n\n";
            }
            else {

                cout << "Error opening file for writing\n\n";
            }
            break;
        }

        case 7: {
            ifstream fin("data.txt");
            if (fin.is_open()) {
                p = LoadPipe(fin, p);
                cs = LoadCS(fin, cs);
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
            cout << "Invalid selection\n\n";
            break;
        }
    }
    return 0;
}
