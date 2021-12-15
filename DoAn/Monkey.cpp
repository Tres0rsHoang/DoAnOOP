#include "Animal.h"

using namespace std;

Monkey::Monkey() {
    this->x = 0;
    this->y = 0;
    this->direction = 0;
    this->length = 10;
}
Monkey::Monkey(screen PlayGround) {
    int* background = PlayGround._getinform();
    this->x = background[0] + 1;
    this->y = background[3] - 9;
    this->direction = 0;
    this->length = 10;
}
Monkey::Monkey(screen PlayGround, int lane, bool right) {
    int* background = PlayGround._getinform();
    if (!right) {
        this->x = background[0] + 1;
        this->y = (background[3] - 5 - 4 * lane);
        this->direction = 0;
        this->length = 10;
        return;
    }
    this->x = background[2] - 17;
    this->y = (background[3] - 5 - 4 * lane);
    this->direction = 1;
    this->length = 10;
}

void Monkey::GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int Monkey::GetX() {
    return this->x;
}
void Monkey::SetX(int x) {
    this->x = x;
}
int Monkey::GetY() { return this->y; }
void Monkey::SetY(int y) { this->y = y; }
bool Monkey::GetDirection() { return this->direction; }
int Monkey::GetLength() { return this->length; }
int Monkey::GetLane() { return this->y; }

void Monkey::_show() {
    if (!this->direction) {
        GotoXY(this->GetX(), this->GetY());
        cout << "      &__&";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "    c['.']";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "\\ _  / \\\\";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "   \\_|   |";
    }
    else {
        GotoXY(this->GetX(), this->GetY());
        cout << " &__&";
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "{'.'}";
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << " //\\   _/";
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << " |  |_/";
    }
}
void Monkey::_destroy() {
    if (!this->direction) {
        GotoXY(this->x, this->y);
        cout << "         ";
        GotoXY(this->x, this->y + 1);
        cout << "         " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "         " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "         " << endl;
    }
    else {
        GotoXY(this->x, this->y);
        cout << "         ";
        GotoXY(this->x, this->y + 1);
        cout << "         " << endl;
        GotoXY(this->x, this->y + 2);
        cout << "          " << endl;
        GotoXY(this->x, this->y + 3);
        cout << "         " << endl;
    }
}