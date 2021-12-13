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
    int length;
    bool direction;
public:
    Animal() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
        this->length = 13;
    }
    Animal(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 8 - 4 * lane);
            this->direction = 0;
            this->length = 13;
            return;
        }
        this->x = background[2] - 21;
        this->y = (background[3] - 8 - 4 * lane);
        this->direction = 1;
        this->length = 13;
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
            cout << "       ___" << endl;
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << "      c '.'/" << endl;
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << "\\_    / \\\\ " << endl;
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << "   \\_|   |" << endl;
        }
        else {
            GotoXY(this->GetX(), this->GetY());
            cout << "__" << endl;
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << "'.'}" << endl;
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << "//\\   _/" << endl;
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << "|  |_/" << endl;
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
        if (!this->GetDirection()) {
            if (this->GetX() < background[2] - this->GetLength() - 1) {
                this->_show();
                Sleep(speed);
                this->_destroy();
                this->SetX(this->GetX() + 1);
                this->_show();
                GotoXY(this->GetX(), this->GetY() + 2);
                cout << "  ";
                GotoXY(this->GetX(), this->GetY() + 3);
                cout << " ";
            }
            else {
                this->_destroy();
                this->SetX(background[0] + 1);
                Sleep(speed);
            }
            this->SetX(this->GetX() + 1);
            this->SetX(this->GetX() + 1);
            pos[0] = this->GetX() - 1;
            pos[1] = this->GetY();
            pos[2] = this->GetX() + this->GetLength() - 3;
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
            pos[0] = this->GetX() + 1;
            pos[1] = this->GetY();
            pos[2] = this->GetX() + this->GetLength() - 2;
            pos[3] = this->GetY() + 3;
        }
        return pos;
    }
};

class Monkey :public Animal {
private:
    int x;
    int y;
    bool direction;
    int length;
public:
    Monkey() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
        this->length = 10;
    }
    Monkey(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 9;
        this->direction = 0;
        this->length = 10;
    }
    Monkey(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 5 - 4 * lane);
            this->direction = 0;
            this->length = 10;
            return;
        }
        this->x = background[2] - 17;
        this->y = (background[3] - 5 - 4 * lane);
        this->direction = 1;
        this->length = 10;
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
    virtual int GetLength() { return this->length; }
    virtual int GetLane() { return this->y; }

    virtual void _show() {
        if (!this->direction) {
            GotoXY(this->GetX(), this->GetY());
            cout << "      &__&";
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << "    c['.']";
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << "\\ _  / \\\\";
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << "   \\_|   |";
        }
        else{
            GotoXY(this->GetX(), this->GetY());
            cout << " &__&";
            GotoXY(this->GetX(), this->GetY() + 1);
            cout << "{'.'}";
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << " //\\   _/";
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << " |  |_/";
        }
    }
    virtual void _destroy() {
        if (!this->direction) {
            GotoXY(this->x, this->y);
            cout << "         ";
            GotoXY(this->x, this->y + 1);
            cout << "         " << endl;
            GotoXY(this->x, this->y + 2);
            cout << "         " << endl;
            GotoXY(this->x, this->y + 3);
            cout << "         " << endl;
        }
        else {
            GotoXY(this->x, this->y);
            cout << "         ";
            GotoXY(this->x, this->y + 1);
            cout << "         " << endl;
            GotoXY(this->x, this->y + 2);
            cout << "          " << endl;
            GotoXY(this->x, this->y + 3);
            cout << "         " << endl;
        }
    }
};
class Moose : public Animal {
private:
    int x;
    int y;
    bool direction;
    int length;
public:
    Moose() {
        this->x = 0;
        this->y = 0;
        this->direction = 0;
        this->length = 10;
    }
    Moose(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 9;
        this->direction = 0;
        this->length = 12;
    }
    Moose(screen PlayGround, int lane, bool right) {
        int* background = PlayGround._getinform();
        if (!right) {
            this->x = background[0] + 1;
            this->y = (background[3] - 5 - 4 * lane);
            this->direction = 0;
            this->length = 12;
            return;
        }
        this->x = background[2] - 17;
        this->y = (background[3] - 5 - 4 * lane);
        this->direction = 1;
        this->length = 12;
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
    virtual int GetLength() { return this->length; }
    virtual int GetLane() { return this->y; }

    virtual void _show() {
        if (!this->direction) {
            GotoXY(this->x, this->y);
            cout << "     =\\\\_//=";
            GotoXY(this->x, this->y + 1);
            cout << "    __/ ''.";
            GotoXY(this->x, this->y + 2);
            cout << " *./ __ |` ";
            GotoXY(this->x, this->y + 3);
            cout << "   ||  ||  ";
        }
        else {
            GotoXY(this->x, this->y);
            cout << "=\\\\//=" << endl;
            GotoXY(this->x, this->y + 1);
            cout << " .''\\__" << endl;
            GotoXY(this->x, this->y + 2);
            cout << "  | __ \\.*" << endl;
            GotoXY(this->x, this->y + 3);
            cout << "  ||  ||" << endl;
        }
    }
    virtual void _destroy() {
        if (!this->direction) {
            GotoXY(this->x, this->y);
            cout << "           ";
            GotoXY(this->x, this->y + 1);
            cout << "           " << endl;
            GotoXY(this->x, this->y + 2);
            cout << "           " << endl;
            GotoXY(this->x, this->y + 3);
            cout << "           " << endl;
        }
        else {
            GotoXY(this->x, this->y);
            cout << "           ";
            GotoXY(this->x, this->y + 1);
            cout << "           " << endl;
            GotoXY(this->x, this->y + 2);
            cout << "           " << endl;
            GotoXY(this->x, this->y + 3);
            cout << "           " << endl;
        }
    }
};

#endif