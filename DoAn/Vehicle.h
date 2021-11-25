#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <thread>

#include "SetScreen.h"

using namespace std;

class Vehicle{
private:
    int x;
    int y;
public:
    Vehicle() {
        this->x = 0;
        this->y = 0;
    }
    Vehicle(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 9;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void _show() {
        GotoXY(this->x, this->y);
        cout << "  ______";
        GotoXY(this->x, this->y + 1);
        cout << " /|_||_\\ `.__";
        GotoXY(this->x, this->y + 2);
        cout << "(   _    _ _\\";
        GotoXY(this->x, this->y + 3);
        cout << "=`-(_)--(_)-' ";
    }
    void _destroy() {
        GotoXY(this->x, this->y);
        cout << "              ";
        GotoXY(this->x, this->y + 1);
        cout << "              " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "              " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "              " << endl;
    }
    void _move(screen PlayGround, int& poscar) {
        int* background = PlayGround._getinform();
        int pos = 0;

        if (poscar < background[2] - 16) {
            this->_destroy();
            this->x += 1;
            this->_show();
            Sleep(30);
        }
        else {
            this->_destroy();
            this->x = pos;
            this->_show();
            poscar = 1;
            Sleep(30);
        }
        poscar++;
    }
};

class Car:public Vehicle{
private:
    int x;
    int y;
public:
    Car() {
        this->x = 0;
        this->y = 0;
    }
    Car(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 9;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void _show() {
        GotoXY(this->x, this->y);
        cout << "  ______                  ______        ";
        GotoXY(this->x, this->y + 1);
        cout << " /|_||_\\`.__            /|_| |_\\`.__   ";
        GotoXY(this->x, this->y + 2);
        cout << "(   _  _    _\\          (   _  _    _\\ ";
        GotoXY(this->x, this->y + 3);
        cout << "=`-(_)- -(_)-'          =`-(_)- -(_)-' ";
    }
    void _destroy() {
        GotoXY(this->x, this->y);
        cout << "                                       ";
        GotoXY(this->x, this->y + 1);
        cout << "                                       " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "                                       " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "                                       " << endl;
    }
    void _move(screen PlayGround, int& i) {
        int* background = PlayGround._getinform();
        int pos = (background[0] + 1);

        if (i < background[2] - 40) {
            this->_destroy();
            this->x += 1;
            this->_show();
            Sleep(30);
        }
        else {
            this->_destroy();
            this->x = pos;
            this->_show();
            i = 1;
            Sleep(30);
        }
        i++;
    }
};

class Truck :public Vehicle{
private:
    int x;
    int y;
public:
    Truck() {
        this->x = 0;
        this->y = 0;
    }
    Truck(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[2] - 25;
        this->y = background[3] - 18;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void _show() {
        GotoXY(this->x, this->y);
        cout << "     ______________ ";
        GotoXY(this->x, this->y + 1);
        cout << "  __|              | ";
        GotoXY(this->x, this->y + 2);
        cout << "/___|   ___   __   | ";
        GotoXY(this->x, this->y + 3);
        cout << "--(_)- --     -(_)== ";
    }
    void _destroy() {
        GotoXY(this->x, this->y);
        cout << "                        ";
        GotoXY(this->x, this->y + 1);
        cout << "                        " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "                        " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "                        " << endl;
    }
    void _move(screen PlayGround, int& i) {
        int* background = PlayGround._getinform();
        int pos = (background[2] - 25);

        if (i < background[2] - 25) {
            this->_destroy();
            this->x -= 1;
            this->_show();
            Sleep(20);
        }
        else {
            this->_destroy();
            this->x = pos;
            this->_show();
            i = 1;
            Sleep(20);
        }
        i++;
    }
};


#endif