#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <thread>

#include "SetScreen.h"

using namespace std;

class Player {

private:
    int x;
    int y;
    int point = 0 ;

public:
    Player() {
        this->x = 0;
        this->y = 0;
    }
    Player(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = (background[2] - background[0]) / 2;
        this->y = background[3] - 3;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void _show() {
        GotoXY(this->x, this->y);
        cout << "\\o/";
        GotoXY(this->x, this->y + 1);
        cout << " | ";
        GotoXY(this->x, this->y + 2);
        cout << "/ \\";
        unsigned int milisecond = 1000;
        //Sleep(50);
        GotoXY(this->x, this->y);
        cout << " o ";
        GotoXY(this->x, this->y + 1);
        cout << "/|\\";
        GotoXY(this->x, this->y + 2);
        cout << "/ \\";
    }
    void _destroy() {
        GotoXY(this->x, this->y);
        cout << "   ";
        GotoXY(this->x, this->y + 1);
        cout << "   " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "   " << endl;
    }
    int getY() {
        return this->y;
    }
    int getPoint() {
        return this->point;
    }
    void showPoint() {
        cout << this->point;
    }
    void setPoint(int a) {
        this->point = a;
    }
    void checkPoint(char choose) {
        if (choose == 'W') {
            switch (this->y)
            {
            case 33:
            case 29:
            case 25:
            case 21:
            case 17:
            case 13:
            case 9:
            case 5:
                this->point += 15;
                break;
            default:
                break;
            }
        }
        else {
            switch (this->y)
            {
            case 34:
            case 30:
            case 26:
            case 22:
            case 18:
            case 14:
            case 10:
            case 6:
                this->point -= 15;
                break;
            default:
                break;
            }
        }
    }
    void _move(screen PlayGround, char choose) {
        int* background = PlayGround._getinform();
        switch (choose) {
        case 'W': {
            if (this->y - 1 < background[3] && this->y - 1 > background[1]) {
                this->_destroy();
                this->y -= 1;
                this->_show();
            }
            this->checkPoint('W');
            break;
        }
        case 'S': {
            if (this->y + 3 < background[3] && this->y + 3 > background[1]) {
                this->_destroy();
                this->y += 1;
                this->_show();
            }
            this->checkPoint('S');
            break;
        }
        case 'D': {
            if (this->x + 3 < background[2] && this->x + 3 > background[0]) {
                this->_destroy();
                this->x += 1;
                this->_show();
            }
            break;
        }
        case 'A': {
            if (this->x - 1 < background[2] && this->x - 1 > background[0]) {
                this->_destroy();
                this->x -= 1;
                this->_show();
            }
            break;
        }
        case 27: {
            GotoXY(this->x + 3, this->y);
            cout << "Done!!";
            Sleep(800);
            GotoXY(this->x + 3, this->y);
            cout << "      ";
            break;
        }
        default:
            GotoXY(this->x + 3, this->y);
            cout << "ERROR MOVING";
            Sleep(800);
            GotoXY(this->x + 3, this->y);
            cout << "             ";
        }

    }

};

#endif