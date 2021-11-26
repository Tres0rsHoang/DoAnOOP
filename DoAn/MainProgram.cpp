#include "Vehicle.h"
#include "Player.h"
#include "SetScreen.h"
#include "Animal.h"

using namespace std;

void Thread_running(bool* Running, char* key, bool& newKey) {

    screen Menu(70, 0, 110, 40);
    screen PlayGround(0, 0, 70, 40);
    screen Display(0, 0, 110, 40);

    Display._format();
    Display._printFrame(6);
    Display._printDisplay(6);

    Player a(PlayGround);
    // =======================================================================
    // PHUONG TIEN GIAO THONG
    Car ca1(PlayGround, 3, 1);
    Car ca2(PlayGround, 2, 0);

    Vehicle* v1 = new Car;
    v1 = &ca1;
    Vehicle* v2 = new Car;
    v2 = &ca2;

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
    // =======================================================================
     // DONG VAT
    Monkey khi_1(PlayGround, 3, 1);
    Monkey khi_2(PlayGround, 2, 0);

    Animal* ani_1 = new Monkey;
    ani_1 = &khi_1;
    Animal* ani_2 = new Monkey;
    ani_2 = &khi_2;

    /*Moose nai_1(PlayGround , 3 , 1);
    Moose nai_2(PlayGround);

    Animal* moose_1 = new Moose;
    moose_1 = &nai_1;
    Animal* moose_2 = new Moose;
    moose_2 = &nai_2;*/

    int posAni1 = 1;
    int posAni2 = 1;

    /*int posMoose_1 = 1;
    int posMoose_2 = 1;*/
    // =======================================================================
    int display_x = 47, display_y = 25;
    int choose = 25;
    bool RunningGame = false;
    while (*Running) {
        if (newKey && !RunningGame) {
            choose = Display.displayMove(display_x, display_y, toupper(*key));
            if (*key == 13) {
                if (choose == 25) {
                    system("cls");
                    Menu._printFrame(6);
                    PlayGround._printFrame(6);
                    a._show();
                    RunningGame = true;
                }
            }
            newKey = false;
        }
        if (RunningGame) {
            v1->_move(PlayGround, 50, 16);
            v2->_move(PlayGround, 50, 16);
            ani_1->_move(PlayGround, 50, 15);
            ani_2->_move(PlayGround, 50, 15);
            /*moose_1->_move(PlayGround, 20, 16);*/
            v1->_move(PlayGround, 10, 16);
            v2->_move(PlayGround, 10, 16);
            if (newKey) {
                a._move(PlayGround, toupper(*key));
                newKey = false;
            }
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