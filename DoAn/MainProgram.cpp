#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <thread>
#include "SetScreen.h"

using namespace std;

class Player {
private:
    int x;
    int y;
public:
    Player() {
        this->x = 0;
        this->y = 0;
    }
    Player(screen PlayGround) {
        int* background = PlayGround._getinform();
        this->x = (background[2] - background[0]) / 2;
        this->y = background[3] - 3;
    }

    void GotoXY(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void _show() {
        GotoXY(this->x, this->y);
        cout << "\\o/";
        GotoXY(this->x, this->y + 1);
        cout << " | ";
        GotoXY(this->x, this->y + 2);
        cout << "/ \\";
        unsigned int milisecond = 1000;
        Sleep(50);
        GotoXY(this->x, this->y);
        cout << " o ";
        GotoXY(this->x, this->y + 1);
        cout << "/|\\";
        GotoXY(this->x, this->y + 2);
        cout << "/ \\";
    } 
    void _destroy() {
        GotoXY(this->x, this->y);
        cout << "   ";
        GotoXY(this->x, this->y + 1);
        cout << "   " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "   " << endl;
    }
    void _move(screen PlayGround){
        int* background = PlayGround._getinform();
        bool stop = false;
       
        while (!stop) {
            char choose = toupper(_getch());
            switch (choose) {
            case 'W': {
                if (this->y - 1 < background[3] && this->y - 1 > background[1]) {
                    this->_destroy();
                    this->y -= 1;
                    this->_show();
                }
                break;
            }
            case 'S': {
                if (this->y + 3 < background[3] && this->y + 3 > background[1]) {
                    this->_destroy();
                    this->y += 1;
                    this->_show();
                }
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
                stop = true;
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
        GotoXY(this->x + 3, this->y);
        cout << "DONE!!!";
        
    }
};

class Vehicle
{
private:
    int x;
    int y;
public:
    Vehicle() {
        this->x = 0;
        this->y = 0;
    }
    Vehicle(screen Truck) {
        int* background = Truck._getinform();
        this->x = (background[2] - background[0]/2);
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
        cout << " /|_||_\ `.__";
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
    void _move(screen Truck){
        int* background = Truck._getinform();
        int pos = this->x;
        int i = 1;

        while (true) {
            if (i < 50)
            {
                this->_destroy();
                this->x += 1;
                this->_show();
                unsigned int milisecond = 100;
                Sleep(15);
                this->_destroy();
            }
           else {
               this->x = pos;
               i = 1;
            }
            i++;
        }

    }
};


int main() {
    screen Menu(66, 0, 100, 40);
    Menu._format();
    Menu._printFrame(6);

    screen PlayGround(0, 0, 66, 40);
    PlayGround._printFrame(6);
    
    
    Player a(PlayGround);
    a._show();

    //thread t1(&Player::_move, a, PlayGround);
   // t1.join();

    screen Truck(0, 0,2, 40);
    Vehicle b(Truck);
    b._show();

    thread t2(&Vehicle::_move, b, Truck);
    t2.join();

    char delay = _getch();
    return 0;
}
