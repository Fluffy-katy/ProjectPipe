#include "Utilites.h"
#include "Station.h"
#include "Pipe.h"
#include "GTS.h"
#include <format>
#include <chrono>



using namespace std;
using namespace chrono;

 
// main

int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "ru");


    redirect_stream_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("Logs/log_" + time + ".txt");

    if (logfile)
        cerr_out.redirect(logfile);


    GTS GasSystem;

    while (1) {
        ENTER;
        cout << "\n1. Add pipe\n" <<
            "2. Add compressor station\n" <<
            "3. Show all objects\n" <<
            "4. Edit\n" <<
            "5. Delete\n" <<
            "6. Search by filter\n" <<
            "7. Save data\n" <<
            "8. Load data\n" <<
            "0. Exit\n" << endl;


        switch (GetCorrectNumber(cin, 0, 8))
        {

        case 1:
        {
            GasSystem.CreatePipe();
            break;
        }
        case 2:
        {
            GasSystem.CreateCS();
            break;
        }

        case 3:
        {
            GasSystem.View();
            break;
        }

        case 4:
        {
            GasSystem.Edit();
            break;
        }

        case 5: {
            GasSystem.Delete();
            break;
        }

        case 6: {
            GasSystem.Search();
            break;
        }

        case 7: {
            GasSystem.SaveConfiguration();
            break;
        }

        case 8: {
            GasSystem.LoadConfiguration();
            break;
        }

        case 0: {
            return 0;

        }
        }
    }

    return 0;
}

