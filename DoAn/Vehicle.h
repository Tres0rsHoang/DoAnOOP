#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <thread>

#include "SetScreen.h"

using namespace std;

class Vehicle {
private:
    int x;
    int y;
    bool direction;
public:
    Vehicle() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
    }
    Vehicle(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 8 - 4 * lane);
            this->direction = 0;
            return;
        }
        this->x = background[2] - 1;
        this->y = (background[3] - 8 - 4 * lane);
        this->direction = 1;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    virtual void _show() {
        GotoXY(this->GetX(), this->GetY());
        cout << "  _______        ";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << " /|_||_\\ `.__   ";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "(   _      _ _\\ ";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "=`-(_)-  -(_)-'  ";
    }
    virtual void _showReverse() {
        GotoXY(this->GetX(), this->GetY());
        cout << "        _______  ";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "   __.` /_||_|\\ ";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << " /_ _      _   )";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "  '-(_)-  -(_)-`=";
    }
    virtual void _destroy() {
        GotoXY(this->x, this->y);
        cout << "                 ";
        GotoXY(this->x, this->y + 1);
        cout << "                 " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "                 " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "                 " << endl;
    }

    virtual int GetX() { return this->x; }
    virtual void SetX(int x) { this->x = x; }
    virtual int GetY() { return this->y; }
    virtual void SetY(int y) { this->y = y; }
    virtual bool GetDirection() { return this->direction; }

    void _move(screen PlayGround, int speed, int lengtVe) {
        int* background = PlayGround._getinform();
        if (!this->GetDirection()) {
            if (this->GetX() < background[2] - lengtVe) {
                this->_show();
                Sleep(speed);
                this->_destroy();
                this->SetX(this->GetX() + 1);
            }
            else {
                this->SetX(background[0] + 1);
                Sleep(speed);
            }
            this->SetX(this->GetX() + 1);
        }
        else{
            if (this->GetX() > 1) {
                this->_showReverse();
                Sleep(speed);
                this->_destroy();
                this->SetX(this->GetX() - 1);
            }
            else {
                this->SetX(background[2] - lengtVe);
                Sleep(speed);
            }
            this->SetX(this->GetX() - 1);
        }
    }
};

class Car :public Vehicle {
private:
    int x;
    int y;
    bool direction;
public:
    Car() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
    }
    Car(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 9;
        this->direction = 0;
    }
    Car(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 8 - 4 * lane);
            this->direction = 0;
            return;
        }
        this->x = background[2] - 17;
        this->y = (background[3] - 8 - 4 * lane);
        this->direction = 1;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    virtual int GetX() {
        return this -> x;
    }
    virtual void SetX(int x) {
        this->x = x;
    }
    virtual int GetY() { return this->y; }
    virtual void SetY(int y) { this->y = y; }
    virtual bool GetDirection() { return this->direction; }

    virtual void _show() {
        GotoXY(this->GetX(), this->GetY());
        cout << "  _______        ";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << " /|_||_\\ `.__   ";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "(   _  V    _ _\\ ";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "=`-(_)-  -(_)-'  ";
    }
    virtual void _showReverse() {
        GotoXY(this->GetX(), this->GetY());
        cout << "       _______  ";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "   __.` /_||_|\\ ";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << " /_ _   V   _  )";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << " '-(_)-  -(_)-`=";
    }
    virtual void _destroy() {
        GotoXY(this->x, this->y);
        cout << "                ";
        GotoXY(this->x, this->y + 1);
        cout << "                " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "                " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "                " << endl;
    }
};

class Truck :public Vehicle {
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

    virtual int GetX() {
        return this->x;
    }
    virtual void SetX(int x) {
        this->x = x;
    }
    virtual void _show() {
        GotoXY(this->x, this->y);
        cout << "     ______________ ";
        GotoXY(this->x, this->y + 1);
        cout << "  __|              | ";
        GotoXY(this->x, this->y + 2);
        cout << "/___|   ___   __   | ";
        GotoXY(this->x, this->y + 3);
        cout << "--(_)- --     -(_)== ";
    }
    virtual void _destroy() {
        GotoXY(this->x, this->y);
        cout << "                        ";
        GotoXY(this->x, this->y + 1);
        cout << "                        " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "                        " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "                        " << endl;
    }
    virtual void _destroyCol() {
        GotoXY(this->x, this->y);
        cout << " ";
        GotoXY(this->x, this->y + 1);
        cout << " " << endl;
        GotoXY(this->x, this->y + 2);
        cout << " " << endl;
        GotoXY(this->x, this->y + 3);
        cout << " " << endl;
    }
};


#endif