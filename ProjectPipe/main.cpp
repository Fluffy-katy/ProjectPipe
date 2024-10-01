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
    cout << "1. Input pipe data\n"
        << "2. Input compressor station data\n"
        << "3. Display information\n"
        << "4. Change pipe repair state\n"
        << "5. Edit number of operating workshops\n"
        << "6. Save data to file\n"
        << "7. Load data from file\n"
        << "0. Exit\n"
        << "Select an option: ";
}
//ТРУБА
Pipe InputPipe() { //функция возвращает struct Pipe, p позволяет работать с отдельными значениям из Pipe
    Pipe p;// объявление объекта структуры Pipe
    cout << "Enter pipe name: ";
    cin >> ws; //убирает все пробельные символы перед чтением строки
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
//КС
CompressorStation InputCompressorStation() {
    CompressorStation cs;

    cout << "Enter compressor station name: ";
    
    getline(cin, cs.name);

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

//СОХРАНИТЬ/ЗАГРУЗИТЬ
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

bool LoadPipe(ifstream& fin, Pipe& p) {
    if (!(getline(fin >> ws, p.name))) return false;
    if (!(fin >> p.length)) return false;
    if (!(fin >> p.diameter)) return false;
    if (!(fin >> p.in_repair)) return false;
    fin.ignore(10000, '\n');

    return fin.good();
}
bool LoadCS(ifstream & fin, CompressorStation & cs) {
    if (!(getline(fin >> ws, cs.name))) return false;
    if (!(fin >> cs.number_of_workshops)) return false;
    if (!(fin >> cs.active_workshops)) return false;
    if (!(fin >> cs.efficiency)) return false;
    return true;
}

// перечисление(enum) MenuOption; содержит варианты меню, для простого понимания какой вариант выбран в switch-case
// /learn.microsoft.com/ru-ru/cpp/cpp/enumerations-cpp?view=msvc-170
enum MenuOption {
    EXIT = 0,
    INPUT_PIPE = 1,
    INPUT_COMPRESSOR_STATION = 2,
    PRINT_INFO = 3,
    TOGGLE_PIPE_REPAIR_STATE = 4,
    EDIT_COMPRESSOR_STATION_WORKSHOPS = 5,
    SAVE_DATA = 6,
    LOAD_DATA = 7
};

int main() {
    Pipe p;
    CompressorStation cs;

    while (true) {
        PrintMenu();
        int tempSelection;
        while (!(cin >> tempSelection)) { //если ввод CIN это int FAILS то это будет TRUE и функция заработает
            ClearCinBuffer();
            PrintMenu();
        }
        MenuOption selection = static_cast<MenuOption>(tempSelection); //https://riptutorial.com/cplusplus/example/18751/enum-conversions
        //преобразует значение переменной tempSelection (которое имеет тип int) 
        // в значение перечисления MenuOption.
        //позволяет далее в программе использовать перечисление (enum),
        //а не просто числа, что делает код более понятным
        cout << "\n";


        switch (selection) {
        case INPUT_PIPE: //как раз таки введеный int уже стал enum
            p = InputPipe();
            break;

        case INPUT_COMPRESSOR_STATION:
            cs = InputCompressorStation();
            break;

        case PRINT_INFO:
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

        case TOGGLE_PIPE_REPAIR_STATE:
            if (p.name != "None") {
                TogglePipeRepairState(p);
            }
            else {
                cout << "No pipe data available\n\n";
            }
            break;

        case EDIT_COMPRESSOR_STATION_WORKSHOPS:
            if (cs.name != "None") {
                EditCompressorStationWorkshops(cs);
            }
            else {
                cout << "No compressor station data available\n\n";
            }
            break;

        case SAVE_DATA: {
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

        case LOAD_DATA: {
            ifstream fin("data.txt");
            if (fin.is_open()) {
                if (LoadPipe(fin, p) || LoadCS(fin, cs)) {
                    fin.close();
                    cout << "Data successfully loaded\n\n";
                }
                else {
                    cout << "Error loading data from file\n\n";
                }
            }
            else {
                cout << "Error opening file for reading\n\n";
            }
            break;
        }

        case EXIT:
            return 0;

        default:
            cout << "Invalid selection\n\n";
            break;
        }
    }
    return 0;
}
