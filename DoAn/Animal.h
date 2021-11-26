#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <thread>

#include "SetScreen.h"

using namespace std;

class Animal {
private:
    int x;
    int y;
    bool direction;
public:
    Animal() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
    }
    Animal(screen PlayGround, int lane, bool right) {
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
        cout << "       ___" << endl;
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "      c '.'/" << endl;
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "\\_    / \\\\ " << endl;
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "   \\_|   |" << endl;
    }
    virtual void _showReverse() {
        GotoXY(this->GetX(), this->GetY());
        cout << "__" << endl;
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "'.'}" << endl;
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "//\\   _/" << endl;
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "|  |_/" << endl;
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
        else {
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

class Monkey :public Animal {
private:
    int x;
    int y;
    bool direction;
public:
    Monkey() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
    }
    Monkey(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 25;
        this->direction = 0;
    }
    Monkey(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 25 - 4 * lane);
            this->direction = 0;
            return;
        }
        this->x = background[2] - 17;
        this->y = (background[3] - 25 - 4 * lane);
        this->direction = 1;
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
    virtual int GetY() { return this->y; }
    virtual void SetY(int y) { this->y = y; }
    virtual bool GetDirection() { return this->direction; }

    virtual void _show() {
        GotoXY(this->GetX(), this->GetY());
        cout << "       ___" << endl;
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "      c '.')" << endl;
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "\\_    / \\\\ " << endl;
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "   \\_|   |" << endl;
    }
    virtual void _showReverse() {
        GotoXY(this->GetX(), this->GetY());
        cout << " __";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "{'.'}";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << " //\\   _/";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << " |  |_/";
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

class Moose : public Animal {
private:
    int x;
    int y;
    bool direction;
public:
    Moose() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
    }
    Moose(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[2] - 25;
        this->y = background[3] - 20;
        this->direction = 0;
    }
    Moose(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 20 - 4 * lane);
            this->direction = 0;
            return;
        }
        this->x = background[2] - 17;
        this->y = (background[3] - 25 - 4 * lane);
        this->direction = 1;
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
    virtual int GetY() { return this->y; }
    virtual void SetY(int y) { this->y = y; }
    virtual bool GetDirection() { return this->direction; }

    virtual void _show() {
        GotoXY(this->x, this->y);
        cout << "=\\\\//=" << endl;
        GotoXY(this->x, this->y + 1);
        cout << " .''\\__" << endl;
        GotoXY(this->x, this->y + 2);
        cout << "  | __ \\" << endl;
        GotoXY(this->x, this->y + 3);
        cout << "  ||  ||" << endl;
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