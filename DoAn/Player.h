#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <thread>
#include <string>

#include "SetScreen.h"

using namespace std;

class Player {
private:
    string name;
    int x;
    int y;
    int point;
    int life;
    bool status;
public:
    Player() {
        this->name = "";
        this->x = 0;
        this->y = 0;
        this->point = 0;
        this->life = 3;
        this->status = 0;
    }
    Player(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = (background[2] - background[0]) / 2;
        this->y = background[3] - 3;
        this->name = "";
        this->point = 0;
        this->life = 3;
        this->status = 0;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void _show() {
        if (!this->status) {
            GotoXY(this->x, this->y);
            cout << "\\o/";
            GotoXY(this->x, this->y + 1);
            cout << " | ";
            GotoXY(this->x, this->y + 2);
            cout << "/ \\";
            this->status = true;
        }
        else {
            GotoXY(this->x, this->y);
            cout << " o ";
            GotoXY(this->x, this->y + 1);
            cout << "/|\\";
            GotoXY(this->x, this->y + 2);
            cout << "/ \\";
            this->status = false;
        }
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
    int getLife() {
        return this->life;
    }
    void setLife(int life) { this->life = life; }
    string getName() { return this->name; }
    void setName(string name) { this->name = name; }
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
                this->point += 10;
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
                this->point -= 10;
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
    bool _checkCollision(int** carPos, int size) {
        int* pos = new int[4];
        pos[0] = this->x;
        pos[1] = this->y;
        pos[2] = pos[0] + 2;
        pos[3] = pos[1] + 2;
        for (int i = 0;i < size;i++) {
            if (pos[0] <= carPos[i][2] && pos[2] >= carPos[i][0] && 
                pos[3] >= carPos[i][1] && pos[1] <= carPos[i][3])
                return 1;
        }
        return 0;
    }
    void _resetPosition(screen PlayGround) {
        this->_destroy();
        int* background = PlayGround._getinform();
        this->x = (background[2] - background[0]) / 2;
        this->y = background[3] - 3;
        this->_show();
    }
    bool _winCheck() {
        if (this->y <= 2) return 1;
        return 0;
    }
};

#endif