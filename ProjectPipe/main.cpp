#include <iostream>
using namespace std;

struct Pipe {
    string name = "None";
    float length = 0;
    int diameter = 0;
    bool in_repair = 0;


};

void PrintMenu() {
    cout << "\n1. Add a pipe\n" <<
        "2. Add a CS\n" <<
        "3. View all objects\n" <<
        "4. Eddit the pipe\n" <<
        "5. Eddit the CS\n" <<
        "6. Save\n" <<
        "7. Load\n" <<
        "Select an option: " << endl;

}

void ShowInfo(const Pipe& p) {
    cout << "Pipe " << p.name << endl
        << "Lengh: " << p.length << endl
        << "Diameter: " << p.diameter << endl
        << "Condition:(0 - in repair, 1 - in operation): " << p.in_repair << endl;
}




int main() {
    cout << "Hello, World!\n";
    PrintMenu();
}



//template <typename T1, typename T2>
//T1 GetCorrectNumber(T1 min, T2 max)
//{
//    T1 x;
//    while ((std::cin >> x).fail()
//        || std::cin.peek() != '\n'
//        x< min x > max)
//    {
//        std::cin.clear();
//        std::cin.ignore(10000, '\n');
//        std::cout << "Enter a number from " << min << " to " << max << std::endl;
//    }
//    return x;
//}