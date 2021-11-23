#include "Vehicle.h"
#include "Player.h"
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
    void _move(screen PlayGround, char choose){
        int* background = PlayGround._getinform();
        
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
            GotoXY(this->x + 3, this->y);
            cout << "Done!!";
            Sleep(800);
            GotoXY(this->x + 3, this->y);
            cout << "      ";
            break;
        }
        default:
            GotoXY(this->x + 3, this->y);
            cout << "ERROR MOVING";
            Sleep(800);
            GotoXY(this->x + 3, this->y);
            cout << "             ";
        }

        //GotoXY(this->x + 3, this->y);
        //cout << "DONE!!!";

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
    void _move(screen PlayGround, int& i){
        int* background = PlayGround._getinform();
        int pos = (background[0] + 1);

        if (i < background[2] - 15) {
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

void Thread_running(bool* Running, char* key, bool& newKey) {

    screen Menu(66, 0, 100, 40);
    screen PlayGround(0, 0, 66, 40);
    screen Display(0, 0, 100, 40);

    Display._format();

    Display._printFrame(6);

    Menu._printFrame(6);
    PlayGround._printFrame(6);

    Player a(PlayGround);
    a._show();

    Car ca(PlayGround);
    ca._show();

    Truck tr(PlayGround);
    tr._show();

    int poscar = 1;
    int Ghbac = 1;


    while (*Running) {
        Car._move(PlayGround, poscar);
        if (newKey) {
            a._move(PlayGround, toupper(*key));
            newKey = false;
        }
    }
}

int main() {
    bool* run = new bool; *run = true;
    char* key = new char; *key = ' ';
    bool newKey = true;
    cout<<"Hello world!!";
    thread t1(Thread_running, run, key, ref(newKey));

    while (1) {
        *key = _getch();
        newKey = true;

        if ((int)*key == 27) {
            *run = false;
            t1.join();
            break;
        }
    }

    char delay = _getch();
    return 0;
}
