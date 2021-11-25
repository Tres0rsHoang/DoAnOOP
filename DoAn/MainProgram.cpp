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


    Car ca1(PlayGround);
    Car ca2(PlayGround);
    Car ca3(PlayGround);

    Vehicle* b1 = new Car;
    b1 = &ca1;
    Vehicle* b2 = new Car;
    b2 = &ca2;
    Vehicle* b3 = new Car;
    b3 = &ca3;

    Truck tr1(PlayGround);
    Truck tr2(PlayGround);
    Vehicle* c1 = new Truck;
    c1 = &tr1;
    Vehicle* c2 = new Truck;
    c2 = &tr2;

    int poscar1 = 1;
    int poscar2 = 1;

    int postruck1 = 1;
    int postruck2 = 1;




    while (*Running) {
        b1->_move(PlayGround, poscar1, 50, 1, 20);
        if (poscar1 >= 31) {
            b2->_move(PlayGround, poscar2, 50, 1, 20);
        }
        c1->_move(PlayGround, postruck1, 50, 0, 20);
        if (poscar1 >= 31) {
            c2->_move(PlayGround, postruck2, 50, 0, 20);
        }
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
