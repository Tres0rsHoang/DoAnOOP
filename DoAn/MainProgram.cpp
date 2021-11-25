#include "Vehicle.h"
#include "Player.h"
#include "SetScreen.h"

using namespace std;

void Thread_running(bool* Running, char* key, bool& newKey) {

    screen Menu(70, 0, 110, 40);
    screen PlayGround(0, 0, 70, 40);
    screen Display(0, 0, 110, 40);

    Display._format();
    Display._printFrame(6);
    Display._printDisplay(6);


   
    int display_x = 47, display_y = 25;
    int choose = 25;
    while (*Running) {
        if (newKey) {
            choose = Display.displayMove(display_x, display_y, toupper(*key));
            if (*key == 13) {
                if (choose == 25) {
                    system("cls");
                    Menu._printFrame(6);
                    PlayGround._printFrame(6);
                }
            }
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
