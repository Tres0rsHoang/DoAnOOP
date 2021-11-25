#include "Vehicle.h"
#include "Player.h"
#include "SetScreen.h"

using namespace std;

void Thread_running(bool* Running, char* key, bool& newKey) {

    screen Menu(66, 0, 100, 40);
    screen PlayGround(0, 0, 66, 40);
    screen Display(0, 0, 100, 40);

    Display._format();

    Display._printFrame(6);

    Menu._printFrame(6);
    PlayGround._printFrame(6);

    Player a(PlayGround);
    a._show();

    Car ca(PlayGround);
    ca._show();

    Truck tr(PlayGround);
    tr._show();

    int poscar = 1;
    int Ghbac = 1;


    while (*Running) {
        ca._move(PlayGround, poscar);
        if (newKey) {
            a._move(PlayGround, toupper(*key));
            newKey = false;
        }
    }
}

int main() {
    bool* run = new bool; *run = true;
    char* key = new char; *key = ' ';
    bool newKey = true;

    thread t1(Thread_running, run, key, ref(newKey));

    while (1) {
        *key = _getch();
        newKey = true;

        if ((int)*key == 27) {
            *run = false;
            t1.join();
            break;
        }
    }

    char delay = _getch();
    return 0;
}
