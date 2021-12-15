#include "Animal.h"

using namespace std;

Moose::Moose() {
    this->x = 0;
    this->y = 0;
    this->direction = 0;
    this->length = 10;
}
Moose::Moose(screen PlayGround) {
    int* background = PlayGround._getinform();
    this->x = background[0] + 1;
    this->y = background[3] - 9;
    this->direction = 0;
    this->length = 12;
}
Moose::Moose(screen PlayGround, int lane, bool right) {
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
void Moose::GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int Moose::GetX() {
    return this->x;
}
void Moose::SetX(int x) {
    this->x = x;
}
int Moose::GetY() { return this->y; }
void Moose::SetY(int y) { this->y = y; }
bool Moose::GetDirection() { return this->direction; }
int Moose::GetLength() { return this->length; }
int Moose::GetLane() { return this->y; }

void Moose::_show() {
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
void Moose::_destroy() {
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