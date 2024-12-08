#include "Utilites.h"
#include "Station.h"
#include "Pipe.h"
#include "GTS.h"
#include <format>
#include <chrono>
#include "Menu.h"

using namespace std;
using namespace chrono;


// main
int main(int argc, char* argv[])
{

    redirect_stream_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("Logs/log_" + time + ".txt");

    if (logfile) cerr_out.redirect(logfile);

    GTS GasSystem;
    MainMenu(GasSystem);
}
