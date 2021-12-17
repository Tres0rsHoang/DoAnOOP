#include "Vehicle.h"

using namespace std;

Car::Car() {
    this->x = 0;
    this->y = 0;
    this->direction = 0;
    this->length = 16;
}
Car::Car(screen PlayGround) {
    int* background = PlayGround._getinform();
    this->x = background[0] + 1;
    this->y = background[3] - 5;
    this->direction = 0;
    this->length = 16;
}
Car::Car(screen PlayGround, int lane, bool right) {
    int* background = PlayGround._getinform();
    if (!right) {
        this->x = background[0] + 1;
        this->y = (background[3] - 5 - 4 * lane);
        this->direction = 0;
        this->length = 16;
        return;
    }
    this->x = background[2] - 17;
    this->y = (background[3] - 5 - 4 * lane);
    this->direction = 1;
    this->length = 16;
}

void Car::GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int Car::GetX() { 
    return this->x; 
}
void Car::SetX(int x) {
    this->x = x;
}
int Car::GetY() { return this->y; }
void Car::SetY(int y) { this->y = y; }
bool Car::GetDirection() { return this->direction; }
int Car::GetLength() { return this->length; }
int Car::GetLane() { return this->y; }

void Car::_show() {
    if (!this->direction) {
        GotoXY(this->GetX(), this->GetY());
        cout << "  _______        ";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << " /|_||_\\ `.__   ";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "(   _  V    _ _\\ ";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "=`-(_)-  -(_)-'  ";
    }
    else {
        GotoXY(this->GetX(), this->GetY());
        cout << "       _______  ";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "   __.` /_||_|\\ ";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << " /_ _   V   _  )";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << " '-(_)-  -(_)-`=";
    }
}
void Car::_destroy() {
    GotoXY(this->x, this->y);
    cout << "                ";
    GotoXY(this->x, this->y + 1);
    cout << "                " << endl;
    GotoXY(this->x, this->y + 2);
    cout << "                " << endl;
    GotoXY(this->x, this->y + 3);
    cout << "                " << endl;
}