#include "Vehicle.h"

using namespace std;

Truck::Truck() {
    this->x = 0;
    this->y = 0;
    this->direction = 0;
    this->length = 20;
}
Truck::Truck(screen PlayGround) {
    int* background = PlayGround._getinform();
    this->x = background[0] + 1;
    this->y = background[3] - 8;
    this->direction = 0;
    this->length = 20;
}
Truck::Truck(screen PlayGround, int lane, bool right) {
    int* background = PlayGround._getinform();
    if (!right) {
        this->x = background[0] + 1;
        this->y = (background[3] - 5 - 4 * lane);
        this->direction = 0;
        this->length = 20;
        return;
    }
    this->x = background[2] - 21;
    this->y = (background[3] - 5 - 4 * lane);
    this->direction = 1;
    this->length = 20;
}
void Truck::GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int Truck::GetX() {
    return this->x;
}
void Truck::SetX(int x) {
    this->x = x;
}
int Truck::GetY() { return this->y; }
void Truck::SetY(int y) { this->y = y; }
bool Truck::GetDirection() { return this->direction; }
int Truck::GetLength() { return this->length; }
int Truck::GetLane() { return this->y; }

void Truck::_show() {
    if (this->direction) {
        GotoXY(this->x, this->y);
        cout << "     ______________ ";
        GotoXY(this->x, this->y + 1);
        cout << "  __|              | ";
        GotoXY(this->x, this->y + 2);
        cout << "/___|   ___   __   | ";
        GotoXY(this->x, this->y + 3);
        cout << "--(_)- --     -(_)== ";
    }
    else {
        GotoXY(this->x, this->y);
        cout << " ______________     ";
        GotoXY(this->x, this->y + 1);
        cout << " |             |__  ";
        GotoXY(this->x, this->y + 2);
        cout << " |   __  ___   |___\\";
        GotoXY(this->x, this->y + 3);
        cout << " ==(_)-    -- -(_)--";
    }
}
void Truck::_destroy() {
    if (!this->direction) {
        GotoXY(this->x, this->y);
        cout << "                    ";
        GotoXY(this->x, this->y + 1);
        cout << "                    " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "                    " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "                    " << endl;
    }
    else {
        GotoXY(this->x, this->y);
        cout << "                     ";
        GotoXY(this->x, this->y + 1);
        cout << "                     " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "                     " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "                     " << endl;
    }
}