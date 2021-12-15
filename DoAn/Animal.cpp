#include "Animal.h"

using namespace std;

Animal::Animal() {
    this->x = 0;
    this->y = 0;
    this->direction = 0;
    this->length = 13;
}
Animal::Animal(screen PlayGround, int lane, bool right) {
    int* background = PlayGround._getinform();
    if (!right) {
        this->x = background[0] + 1;
        this->y = (background[3] - 8 - 4 * lane);
        this->direction = 0;
        this->length = 13;
        return;
    }
    this->x = background[2] - 21;
    this->y = (background[3] - 8 - 4 * lane);
    this->direction = 1;
    this->length = 13;
}

void Animal::GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Animal::_show() {
    if (!this->direction) {
        GotoXY(this->GetX(), this->GetY());
        cout << "       ___" << endl;
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "      c '.'/" << endl;
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "\\_    / \\\\ " << endl;
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "   \\_|   |" << endl;
    }
    else {
        GotoXY(this->GetX(), this->GetY());
        cout << "__" << endl;
        GotoXY(this->GetX(), this->GetY() + 1);
        cout << "'.'}" << endl;
        GotoXY(this->GetX(), this->GetY() + 2);
        cout << "//\\   _/" << endl;
        GotoXY(this->GetX(), this->GetY() + 3);
        cout << "|  |_/" << endl;
    }
}

void Animal::_destroy() {
    GotoXY(this->x, this->y);
    cout << "                 ";
    GotoXY(this->x, this->y + 1);
    cout << "                 " << endl;
    GotoXY(this->x, this->y + 2);
    cout << "                 " << endl;
    GotoXY(this->x, this->y + 3);
    cout << "                 " << endl;
}

int Animal::GetX() { return this->x; }
void Animal::SetX(int x) { this->x = x; }
int Animal::GetY() { return this->y; }
void Animal::SetY(int y) { this->y = y; }
bool Animal::GetDirection() { return this->direction; }
int Animal::GetLength() { return this->length; }
int Animal::GetLane() { return this->y; }

int* Animal::_move(screen PlayGround, int speed) {

    int* background = PlayGround._getinform();
    int* pos = new int[4];
    if (!this->GetDirection()) {
        if (this->GetX() < background[2] - this->GetLength() - 1) {
            this->_show();
            Sleep(speed);
            this->_destroy();
            this->SetX(this->GetX() + 1);
            this->_show();
            GotoXY(this->GetX(), this->GetY() + 2);
            cout << "  ";
            GotoXY(this->GetX(), this->GetY() + 3);
            cout << " ";
        }
        else {
            this->_destroy();
            this->SetX(background[0] + 1);
            Sleep(speed);
        }
        this->SetX(this->GetX() + 1);
        this->SetX(this->GetX() + 1);
        pos[0] = this->GetX() - 1;
        pos[1] = this->GetY();
        pos[2] = this->GetX() + this->GetLength() - 3;
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
        pos[0] = this->GetX() + 1;
        pos[1] = this->GetY();
        pos[2] = this->GetX() + this->GetLength() - 2;
        pos[3] = this->GetY() + 3;
    }

    return pos;
}