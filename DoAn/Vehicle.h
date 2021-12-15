
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
    Vehicle();
    Vehicle(screen PlayGround, int lane, bool right);

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

class Car :public Vehicle {
private:
    int x;
    int y;
    bool direction;
    int length;
public:
    Car();
    Car(screen PlayGround);
    Car(screen PlayGround, int lane, bool right);

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

class Truck :public Vehicle {
private:
    int x;
    int y;
    bool direction;
    int length;
public:
    Truck();
    Truck(screen PlayGround);
    Truck(screen PlayGround, int lane, bool right);
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