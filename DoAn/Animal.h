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
    Animal();
    Animal(screen PlayGround, int lane, bool right);

    void GotoXY(int x, int y);
    virtual void _show();

    virtual void _destroy();

    virtual int GetX();
    virtual void SetX(int x);
    virtual int GetY();
    virtual void SetY(int y);
    virtual bool GetDirection();
    virtual int GetLength();
    virtual int GetLane();

    int* _move(screen PlayGround, int speed);
};

class Monkey :public Animal {
private:
    int x;
    int y;
    bool direction;
    int length;
public:
    Monkey();
    Monkey(screen PlayGround);
    Monkey(screen PlayGround, int lane, bool right);

    void GotoXY(int x, int y);

    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);
    bool GetDirection();
    int GetLength();
    int GetLane();

    void _show();
    void _destroy();
};
class Moose : public Animal {
private:
    int x;
    int y;
    bool direction;
    int length;
public:
    Moose();
    Moose(screen PlayGround);
    Moose(screen PlayGround, int lane, bool right);
    void GotoXY(int x, int y);

    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);
    bool GetDirection();
    int GetLength();
    int GetLane();

    void _show();
    void _destroy();
};

#endif