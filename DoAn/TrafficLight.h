#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_
#include <ctime>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "SetScreen.h"

using namespace std;

class TrafficLight {
    int status;
    int lane;
    int x;
    int baseTime;
    int time;
public:
    TrafficLight() {
        this->status = 0;
        this->lane = 0;
        this->x = 0;
        this->baseTime = 0;
        this->time = 0;
    }
    TrafficLight(screen Light, int lane, int status, int time) {
        int* background = Light._getinform();
        this->lane = lane + 1;
        this->x = background[0] + abs(background[2] - background[0]) / 2;
        this->status = status;
        this->time = this->baseTime = time;
    }
    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void SetColor(int backgound_color, int text_color) {
        /*
        0 = Black      8 = Gray
        1 = Blue       9 = Light Blue
        2 = Green      10 = Light Green
        3 = Aqua       11 = Light Aqua
        4 = Red        12 = Light Red
        5 = Purple     13 = Light Purple
        6 = Yellow     14 = Light Yellow
        7 = White      15 = Bright White
        */
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        int color_code = backgound_color * 16 + text_color;
        SetConsoleTextAttribute(hStdout, color_code);
    }
    int GetStatus() { return this->status; }
    void _show() {
        if (this->status == 0) {
            GotoXY(this->x, this->lane + 2);
            SetColor(0, 2);
            cout << (char)177;
        }
        if (this->status == 1) {
            GotoXY(this->x, this->lane + 1);
            SetColor(0, 6);
            cout << (char)177;
        }
        if (this->status == 2) {
            GotoXY(this->x, this->lane);
            SetColor(0, 4);
            cout << (char)177;
        }
        SetColor(0, 7);
    }
    void _changeAndShow() {
        GotoXY(this->x + 1, this->lane);
        cout << "  ";
        GotoXY(this->x + 1, this->lane);
        this->time--;
        cout << time;
        if (time == 0) {
            this->status++;
            if (this->status > 2) this->status = 0;
            if (this->status == 0) {
                GotoXY(this->x, this->lane);
                cout << " ";
                GotoXY(this->x, this->lane + 2);
                SetColor(0, 10);
                cout << (char)177;
                SetColor(0, 7);
            }
            if (this->status == 1) {
                GotoXY(this->x, this->lane + 2);
                cout << " ";
                GotoXY(this->x, this->lane + 1);
                SetColor(0, 6);
                cout << (char)177;
                SetColor(0, 7);
            }
            if (this->status == 2) {
                GotoXY(this->x, this->lane + 1);
                cout << " ";
                GotoXY(this->x, this->lane);
                SetColor(0, 12);
                cout << (char)177;
                SetColor(0, 7);
            }
            this->time = this->baseTime;
        }
        SetColor(0, 7);
    }
};

#endif