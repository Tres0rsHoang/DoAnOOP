#define _CRT_SECURE_NO_WARNINGS
#include "Vehicle.h"
#include "Player.h"
#include "SetScreen.h"
#include "Animal.h"
#include "TrafficLight.h"
#include "GameLibrary.h"

using namespace std;

int main() {
    srand(time(NULL));

    bool* run = new bool; *run = true;
    char* key = new char; *key = ' ';
    bool newKey = true;

    DWORD dwVolume;

    //Set Max volume
    waveOutSetVolume(NULL, 0xFFFF);

    thread t1(Thread_running, run, key, ref(newKey));

    while (1) {
        *key = _getch();
        newKey = true;
    }

    char delay = _getch();
    
    return 0;
}