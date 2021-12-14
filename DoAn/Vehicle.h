
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
    int length;
    bool direction;
public:
    Vehicle() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
        this->length = 16;
    }
    Vehicle(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 8 - 4 * lane);
            this->direction = 0;
            this->length = 16;
            return;
        }
        this->x = background[2] - 1;
        this->y = (background[3] - 8 - 4 * lane);
        this->direction = 1;
        this->length = 16;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    virtual void _show() {
        if (!this->direction) {
            GotoXY(this->GetX(), this->GetY());
            cout << "  _______        ";
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << " /|_||_\\ `.__   ";
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << "(   _      _ _\\ ";
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << "=`-(_)-  -(_)-'  ";
        }
        else {
            GotoXY(this->GetX(), this->GetY());
            cout << "        _______  ";
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << "   __.` /_||_|\\ ";
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << " /_ _      _   )";
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << "  '-(_)-  -(_)-`=";
        }
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
    virtual int GetLength() { return this->length; }
    virtual int GetLane() { return this->y; }

    int* _move(screen PlayGround, int speed) {
        int* background = PlayGround._getinform();
        int* pos = new int[4];
        //GotoXY(0, 0);
        if (!this->GetDirection()) {
            if (this->GetX() < background[2] - this->GetLength() - 1) {
                this->_show();
                Sleep(speed);
                this->_destroy();
                this->SetX(this->GetX() + 1);
                this->_show();
                GotoXY(this->GetX(), this->GetY() + 2);
                cout << " ";
                GotoXY(this->GetX(), this->GetY() + 3);
                cout << " ";
            }
            else {
                this->_destroy();
                this->SetX(background[0] + 1);
                Sleep(speed);
            }
            this->SetX(this->GetX() + 1);
            pos[0] = this->GetX();
            pos[1] = this->GetY();
            pos[2] = this->GetX() + this->GetLength() - 2;
            pos[3] = this->GetY() + 3;
        }
        else {
            if (this->GetX() > 2) {
                this->_show();
                Sleep(speed);
                this->_destroy();
                this->SetX(this->GetX() - 1);
                this->_show();
                GotoXY(this->GetX() + this->GetLength() + 1, this->GetY() + 2);
                cout << " ";
                GotoXY(this->GetX() + this->GetLength() + 1, this->GetY() + 3);
                cout << " ";
            }
            else {
                this->_destroy();
                GotoXY(this->GetX() + this->GetLength(), this->GetY() + 2);
                cout << " ";
                GotoXY(this->GetX() + this->GetLength(), this->GetY() + 3);
                cout << " ";
                this->SetX(background[2] - this->GetLength());
                Sleep(speed);
            }
            this->SetX(this->GetX() - 1);
            pos[0] = this->GetX() + 2;
            pos[1] = this->GetY();
            pos[2] = this->GetX() + this->GetLength();
            pos[3] = this->GetY() + 3;
        }
        return pos;
    }
};

class Car :public Vehicle {
private:
    int x;
    int y;
    bool direction;
    int length;
public:
    Car() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
        this->length = 16;
    }
    Car(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 5;
        this->direction = 0;
        this->length = 16;
    }
    Car(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 5 - 4 * lane);
            this->direction = 0;
            this->length = 16;
            return;
        }
        this->x = background[2] - 17;
        this->y = (background[3] - 5 - 4 * lane);
        this->direction = 1;
        this->length = 16;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    int GetX() { return this->x; }
    void SetX(int x) {
        this->x = x;
    }
    int GetY() { return this->y; }
    void SetY(int y) { this->y = y; }
    bool GetDirection() { return this->direction; }
    int GetLength() { return this->length; }
    int GetLane() { return this->y; }

    void _show() {
        if (!this->direction) {
            GotoXY(this->GetX(), this->GetY());
            cout << "  _______        ";
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << " /|_||_\\ `.__   ";
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << "(   _  V    _ _\\ ";
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << "=`-(_)-  -(_)-'  ";
        }
        else {
            GotoXY(this->GetX(), this->GetY());
            cout << "       _______  ";
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << "   __.` /_||_|\\ ";
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << " /_ _   V   _  )";
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << " '-(_)-  -(_)-`=";
        }
    }
    void _destroy() {
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
    bool direction;
    int length;
public:
    Truck() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
        this->length = 20;
    }
    Truck(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 8;
        this->direction = 0;
        this->length = 20;
    }
    Truck(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 5 - 4 * lane);
            this->direction = 0;
            this->length = 20;
            return;
        }
        this->x = background[2] - 21;
        this->y = (background[3] - 5 - 4 * lane);
        this->direction = 1;
        this->length = 20;
    }
    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    int GetX() {
        return this->x;
    }
    void SetX(int x) {
        this->x = x;
    }
    int GetY() { return this->y; }
    void SetY(int y) { this->y = y; }
    bool GetDirection() { return this->direction; }
    int GetLength() { return this->length; }
    int GetLane() { return this->y; }

    void _show() {
        if (this->direction) {
            GotoXY(this->x, this->y);
            cout << "     ______________ ";
            GotoXY(this->x, this->y + 1);
            cout << "  __|              | ";
            GotoXY(this->x, this->y + 2);
            cout << "/___|   ___   __   | ";
            GotoXY(this->x, this->y + 3);
            cout << "--(_)- --     -(_)== ";
        }
        else {
            GotoXY(this->x, this->y);
            cout << " ______________     ";
            GotoXY(this->x, this->y + 1);
            cout << " |             |__  ";
            GotoXY(this->x, this->y + 2);
            cout << " |   __  ___   |___\\";
            GotoXY(this->x, this->y + 3);
            cout << " ==(_)-    -- -(_)--";
        }
    }
    void _destroy() {
        if (!this->direction) {
            GotoXY(this->x, this->y);
            cout << "                    ";
            GotoXY(this->x, this->y + 1);
            cout << "                    " << endl;
            GotoXY(this->x, this->y + 2);
            cout << "                    " << endl;
            GotoXY(this->x, this->y + 3);
            cout << "                    " << endl;
        }
        else {
            GotoXY(this->x, this->y);
            cout << "                     ";
            GotoXY(this->x, this->y + 1);
            cout << "                     " << endl;
            GotoXY(this->x, this->y + 2);
            cout << "                     " << endl;
            GotoXY(this->x, this->y + 3);
            cout << "                     " << endl;
        }
    }
};

#endif