#include "Vehicle.h"
#include "Player.h"
#include "SetScreen.h"
#include "Animal.h"
#include <ctime>
#include <vector>

using namespace std;


void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Thread_running(bool* Running, char* key, bool& newKey) {
    screen Menu(70, 0, 110, 40);
    screen PlayGround(0, 0, 70, 40);
    screen Display(0, 0, 110, 40);

    Display._format();
    Display._printFrame(6);
    Display._printDisplay(6);

    Player a(PlayGround);
    /*Car ca1(PlayGround, 2, 1);
    Car ca2(PlayGround, 3, 0);
    Car ca3(PlayGround, 5, 1);
    Car ca4 (PlayGround, 6, 0);
    Car ca5 (PlayGround, 7, 1);
    Truck tr1(PlayGround, 1, 1);
    Truck tr2(PlayGround, 4, 0);

    vector<Vehicle*> listCar;
    listCar.resize(7, new Car);
    listCar[0] = &tr1;
    listCar[1] = &ca2;
    listCar[2] = &tr1;
    listCar[3] = &tr2;
    listCar[4] = &ca3;
    listCar[5] = &ca4;
    listCar[6] = &ca5;*/

    Monkey khi_1(PlayGround, 5, 1);
    Monkey khi_2(PlayGround, 3, 0);
    Moose nai_1(PlayGround, 1, 1);
    Moose nai_2(PlayGround, 2, 0);

    vector<Animal*> listAnimal;
    listAnimal.resize(4, new Monkey);
    listAnimal[0] = &khi_1;
    listAnimal[1] = &khi_2;
    listAnimal[2] = &nai_1;
    listAnimal[3] = &nai_2;
    
    int display_x = 47, display_y = 25;
    int choose = 25;
    bool RunningGame = false;
    /*int** carPos = new int*[7];
    for (int i = 0;i < 7;i++)
        carPos[i] = new int[4];*/

    int** animalPos = new int* [4];
    for (int i = 0; i < 4; i++)
        animalPos[i] = new int[4];
  
    while (*Running) {
        if (newKey && !RunningGame) {
            choose = Display.displayMove(display_x, display_y, toupper(*key));
            if (*key == 13) {
                if (choose == 25) {
                    system("cls");
                    Menu._printFrame(6);
                    PlayGround._printFrame(6);
                    a._show(); 
                    //animalPos[3] = listAnimal[3]->_move(PlayGround, 100);
                    RunningGame = true;
                }
            }
            newKey = false;
        }

        //Test va cham xe
        /*if (RunningGame) {
            for (int i = 0; i <= 6; i++) {
                if (rand() % 10 == 1) {
                    carPos[i] = listCar[i]->_move(PlayGround, 100);
                }
            }
            if (newKey) {
                a._move(PlayGround, toupper(*key));
                newKey = false;
            }
            GotoXY(75, 20);
            cout << a._checkCollision(carPos, 7);
        }*/
        //Test va cham dong vat
        if (RunningGame) {
            for (int i = 0; i <= 3; i++) {
                if (rand() % 10 == 1) {
                    animalPos[i] = listAnimal[i]->_move(PlayGround, 100);
                }
            }
            if (newKey) {
                a._move(PlayGround, toupper(*key));
                newKey = false;
            }
            GotoXY(75, 20);
            cout << a._checkCollision(animalPos, 4);
        }
    }
}

int main() {
    srand(time(NULL));
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