#define _CRT_SECURE_NO_WARNINGS
#include "Vehicle.h"
#include "Player.h"
#include "SetScreen.h"
#include "Animal.h"
#include "TrafficLight.h"

using namespace std;

void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameLoad(screen PlayGround, screen Light, 
    vector<Vehicle*>& listCar, vector<TrafficLight>& listLight, int level) {
    listCar.clear();
    listLight.clear();
    bool Lane[9];
    for (int i = 0;i <= 8;i++) Lane[i] = false;
    int carNumber = 0;
    int truckNumber = 0;
    int TrueLevel = 0;
    if (level <= 10 && level > 0) TrueLevel = 1;
    else if (level >= 11 && level <= 20) TrueLevel = 2;
    else if (level >= 21) TrueLevel = 3;
    if (TrueLevel == 1) {
        carNumber = rand() % 3;
        truckNumber = abs((rand() % 3) - carNumber);
    }
    else if (TrueLevel == 2) {
        carNumber = rand() % 5;
        truckNumber = abs((rand() % 5) - carNumber);
    }
    else if (TrueLevel == 3) {
        carNumber = rand() % 8;
        truckNumber = abs((rand() % 8) - carNumber);
    }
    
    while (carNumber > 0) {
        int tempLane = rand() % 9;
        if (tempLane == 0) continue;
        if (!Lane[tempLane]) {
            Car* tempCar = new Car(PlayGround, tempLane, rand() % 2);
            listCar.push_back(tempCar);
            carNumber--;
            Lane[tempLane] = true;
        }
    }
    while (truckNumber > 0) {
        int tempLane = rand() % 9;
        if (tempLane == 0) continue;
        if (!Lane[tempLane]) {
            Truck* tempCar = new Truck(PlayGround, tempLane, rand() % 2);
            listCar.push_back(tempCar);
            truckNumber--;
            Lane[tempLane] = true;
        }
    }
    if (TrueLevel == 1) {
        for (unsigned int i = 0;i < listCar.size();i++) {
            listLight.push_back(TrafficLight(Light, listCar[i]->GetLane(), rand() % 3, rand() % 20 + 2));
        }
    }
    else if (TrueLevel == 2) {
        for (unsigned int i = 0;i < listCar.size();i++) {
            listLight.push_back(TrafficLight(Light, listCar[i]->GetLane(), rand() % 3, rand() % 15 + 2));
        }
    }
    else if (TrueLevel == 3) {
        for (unsigned int i = 0;i < listCar.size();i++) {
            listLight.push_back(TrafficLight(Light, listCar[i]->GetLane(), rand() % 3, rand() % 10 + 2));
        }
    }
    
}
void Thread_running(bool* Running, char* key, bool& newKey) {
    srand(time(NULL));
    screen Menu(70, 0, 110, 40);
    screen PlayGround(0, 0, 65, 40);
    screen Display(0, 0, 110, 40);
    screen Light(65, 0, 70, 40);
    Player a(PlayGround);
    Display._format();
Again:
    system("cls");
    Display._printFrame(6);
    Display._printDisplay(6);

    vector<Vehicle*> listCar;
    vector<TrafficLight> listLight;

    time_t now = time(0);
    tm* ltm = localtime(&now);
    int sec = 1 + ltm->tm_sec;
    int preSec = sec;

    int display_x = 47, display_y = 25;
    int choose = 25;
    bool RunningGame = false;
    int** carPos = new int*[listCar.size()];
    int level = 5;

    while (*Running) {
        if (newKey && !RunningGame) {
            choose = Display.displayMove(display_x, display_y, toupper(*key));
            if (*key == 13) {
                if (choose == 25) {
                    system("cls");
                    a.setName(Display._inputNameScreen(6));
                    system("cls");
                    Menu._printFrame(6);
                    Menu._printScoreMenu(6, 0, a.getName(), a.getLife(), level);
                    PlayGround._printFrame(6);
                    a._show();

                    GameLoad(PlayGround, Light, listCar, listLight, level);
                    delete[] carPos;
                    carPos = new int* [listCar.size()];
                    for (unsigned int i = 0; i < listCar.size(); i++)
                        carPos[i] = new int[4];
                    Light._printLightFrame(6);
                    for (unsigned int i = 0;i < listLight.size();i++) listLight[i]._show();
                    RunningGame = true;
                }
            }
            newKey = false;
        }

        //Test va cham xe
        if (RunningGame) {
            now = time(0);
            ltm = localtime(&now);
            sec = 1 + ltm->tm_sec;
            if (sec != preSec) {
                preSec = sec;
                for (unsigned int i = 0;i < listLight.size();i++)
                    listLight[i]._changeAndShow();
            }
            for (unsigned int i = 0;i < listCar.size();i++)
                if (rand() % 10 == 1 && listLight[i].GetStatus() != 2) 
                    carPos[i] = listCar[i]->_move(PlayGround, 100);

            if (newKey) {
                a._move(PlayGround, toupper(*key));
                newKey = false;
            }
            if (a._checkCollision(carPos, listCar.size())) {
                a.setLife(a.getLife() - 1);
                a._resetPosition(PlayGround);
            }
            if (a.getLife() == 0) {
                system("cls");
                Display._loseScreen();
                break;
            }
            Menu._printScoreMenu(6, a.getPoint(), a.getName(), a.getLife(), level);
            if (a._winCheck()) {
                system("cls");
                level++;
                Menu._printFrame(6);
                Menu._printScoreMenu(6, 0, a.getName(), a.getLife(), level);
                PlayGround._printFrame(6);
                a._resetPosition(PlayGround);
                GameLoad(PlayGround, Light, listCar, listLight, level);
                delete carPos;
                carPos = new int* [listCar.size()];
                for (unsigned int i = 0; i < listCar.size(); i++)
                    carPos[i] = new int[4];
                Light._printLightFrame(6);
                for (unsigned int i = 0;i < listLight.size();i++) listLight[i]._show();
            }
        }
    }
    char delay = _getch();
    goto Again;
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
    //cout << rand() % 10 << " ";
    char delay = _getch();
    
    return 0;
}