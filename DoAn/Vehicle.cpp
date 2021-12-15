#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle() {
    this->x = 0;
    this->y = 0;
    this->direction = 0;
    this->length = 16;
}
Vehicle::Vehicle(screen PlayGround, int lane, bool right) {
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

void Vehicle::GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Vehicle::_show() {
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

void Vehicle::_destroy() {
    GotoXY(this->x, this->y);
    cout << "                 ";
    GotoXY(this->x, this->y + 1);
    cout << "                 " << endl;
    GotoXY(this->x, this->y + 2);
    cout << "                 " << endl;
    GotoXY(this->x, this->y + 3);
    cout << "                 " << endl;
}

int Vehicle::GetX() { return this->x; }
void Vehicle::SetX(int x) { this->x = x; }
int Vehicle::GetY() { return this->y; }
void Vehicle::SetY(int y) { this->y = y; }
bool Vehicle::GetDirection() { return this->direction; }
int Vehicle::GetLength() { return this->length; }
int Vehicle::GetLane() { return this->y; }

int* Vehicle::_move(screen PlayGround, int speed) {
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