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
public:
    Animal() {
        this->x = 0;
        this->y = 0;
    }
    Animal(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 40;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    virtual void increaseX() {
        this->x += 1;
    }
    virtual void baseX(int p) {
        this->x = p;
    }
    virtual void decreaseX() {
        this->x -= 1;
    }
    virtual void _show() {
        GotoXY(this->x, this->y);
        cout << "       ___" << endl;
        GotoXY(this->x, this->y + 1);
        cout << "      c '.'" << endl;
        GotoXY(this->x, this->y + 2);
        cout << "\\_    / \\\\ " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "   \\_|    |" << endl;
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

    //void _move(screen PlayGround,int prelength, int length, int& poscar, bool direction, int speed) {
    void _move(screen PlayGround, int& posAnimal, int speed, bool direction, int lengtVe) {

        if (direction) {
            int* background = PlayGround._getinform();
            int pos = (background[0] + 1);
            if (posAnimal < background[2] - lengtVe) {

                this->_destroy();
                this->increaseX();
                this->_show();
                Sleep(speed);
            }
            else {
                this->_destroy();
                this->baseX(pos);
                this->_show();
                posAnimal = 1;
                Sleep(speed);
            }
            posAnimal++;
        }
        else
        {
            int* background = PlayGround._getinform();
            int pos = (background[2] - 25);

            if (posAnimal < background[2] - 25) {
                this->_destroy();
                this->decreaseX();
                this->_show();
                Sleep(20);
            }
            else {
                this->_destroy();
                this->baseX(pos);
                this->_show();
                posAnimal = 1;
                Sleep(20);
            }
            posAnimal++;
        }
    }
};

class Monkey :public Animal {
private:
    int x;
    int y;

public:
    Monkey() {
        this->x = 0;
        this->y = 0;
    }
    Monkey(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[0] + 1;
        this->y = background[3] - 30;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    virtual void increaseX() {
        this->x += 1;
    }
    virtual void baseX(int p) {
        this->x = p;
    }
    virtual void decreaseX() {
        this->x -= 1;
    }
    virtual void _show() {
        GotoXY(this->x, this->y);
        cout << "       ___" << endl;
        GotoXY(this->x, this->y + 1);
        cout << "      c '.'" << endl;
        GotoXY(this->x, this->y + 2);
        cout << "\\_    / \\\\ " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "   \\_|    |" << endl;
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

class Moose : public Animal {

private:
    int x;
    int y;

public:
    Moose() {
        this->x = 0;
        this->y = 0;
    }
    Moose(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = background[2] - 25;
        this->y = background[3] - 35;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    virtual void increaseX() {
        this->x += 1;
    }
    virtual void baseX(int p) {
        this->x = p;
    }
    virtual void decreaseX() {
        this->x -= 1;
    }
    virtual void _show() {
        GotoXY(this->x, this->y);
        cout << "\\\\//" << endl;
        GotoXY(this->x, this->y + 1);
        cout << ".''\\__" << endl;
        GotoXY(this->x, this->y + 2);
        cout << " | __ \\" << endl;
        GotoXY(this->x, this->y + 3);
        cout << " ||  ||" << endl;
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