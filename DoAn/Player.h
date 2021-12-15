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
    int life;
    bool status;
    int level;
    int point;
public:
    Player();
    Player(screen PlayGround);
    Player(screen PlayGround, string name, int point, int life, int level);
    void GotoXY(int x, int y);

    void _show();
    void _destroy();
    int getY();
    int getPoint();
    int getLife();
    void setLife(int life);
    string getName();
    void setName(string name);
    void setLevel(int level);
    int getLevel();
    void showPoint();
    void setPoint(int a);
    void checkPoint(char choose);
    void _move(screen PlayGround, char choose);
    bool _checkCollision(int** carPos, int size);
    void _resetPosition(screen PlayGround);
    bool _winCheck();
    static bool comp(const Player& a, const Player& b);
    Player& operator= (const Player& b);
};

#endif