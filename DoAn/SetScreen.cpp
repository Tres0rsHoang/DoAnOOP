#include "SetScreen.h"

using namespace std;

screen::screen(int x, int y, int z, int t){
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
}
screen::screen() {
	this->x = this->y = this->z = this->t = 0;
}

void screen::SetWindowSize(SHORT width, SHORT height) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;
	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void screen::FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	style &= ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX); //tắt phòng to nhỏ
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void screen::GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void screen::DisableSelection() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}
void screen::SetColor(int backgound_color, int text_color) {
	/*
	0 = Black      8 = Gray
	1 = Blue       9 = Light Blue
	2 = Green      10 = Light Green
	3 = Aqua       11 = Light Aqua
	4 = Red        12 = Light Red
	5 = Purple     13 = Light Purple
	6 = Yellow     14 = Light Yellow
	7 = White      15 = Bright White
	*/
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}
void screen::SetScreenBufferSize(SHORT width, SHORT height) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;
	SetConsoleScreenBufferSize(hStdout, NewSize);
}
void screen::ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
void screen::_input(int x, int y, int z, int t) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
}
void screen::_format() {
	system("cls");
	SetWindowSize(this->z, this->t);
	SetScreenBufferSize(this->z + 1, this->t + 1);
	FixConsoleWindow();
	ShowCur(0);
	DisableSelection();
}
int* screen::_getinform() {
	int* result = new int[4];
	result[0] = this->x;
	result[1] = this->y;
	result[2] = this->z;
	result[3] = this->t;
	return result;
}
void screen::_printFrame(int color) {
	//Vẽ khuôn
	SetColor(0, color);
	for (int i = this->y; i <= this->t;i++) {
		GotoXY(this->x, i);
		cout << (char)219;
		GotoXY(this->z, i);
		cout << (char)219;
	}
	for (int i = this->x;i <= this->z; i++) {
		GotoXY(i, this->y);
		cout << (char)219;
		GotoXY(i, this->t);
		cout << (char)219;
	}
	SetColor(0, 7);
}
void screen::_printLightFrame(int color) {
	//Vẽ khuôn
	SetColor(0, color);
	for (int i = this->y; i <= this->t;i++) {
		GotoXY(this->x, i);
		cout << (char)219;
		GotoXY(this->z, i);
		cout << (char)219;
	}
	for (int i = this->x;i <= this->z; i++) {
		GotoXY(i, this->y);
		cout << (char)219;
		GotoXY(i, this->t);
		cout << (char)219;
		for (int j = 0; j <= 8; j++) {
			GotoXY(i, this->t - 5 - 4 * j);
			cout << (char)219;
		}
	}
	SetColor(0, 7);
}
void screen::_printDisplay(int color) {
	SetColor(0, color);
	GotoXY(6, 11);
	cout << " ______  ______  ______  ______  ______  __  __   __  ______       ______  ______  ______  _____   ";
	GotoXY(6, 12);
	cout << "/\\  ___\\/\\  == \\/\\  __ \\/\\  ___\\/\\  ___\\/\\ \\/\\ \"-.\\ \\/\\  ___\\     /\\  == \\/\\  __ \\/\\  __ \\/\\  __-. ";
	GotoXY(6, 13);
	cout << "\\ \\ \\___\\ \\  __<\\ \\ \\/\\ \\ \\___  \\ \\___  \\ \\ \\ \\ \\-.  \\ \\ \\__ \\    \\ \\  __<\\ \\ \\/\\ \\ \\  __ \\ \\ \\/\\ \\ ";
	GotoXY(6, 14);
	cout << " \\ \\_____\\ \\_\\ \\_\\ \\_____\\/\\_____\\/\\_____\\ \\_\\ \\_\\\\\"\\_\\ \\_____\\    \\ \\_\\ \\_\\ \\_____\\ \\_\\ \\_\\ \\____- ";
	GotoXY(6, 15);
	cout << "  \\/_____/\\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/\\/_/ \\/_/\\/_____/     \\/_/ /_/\\/_____/\\/_/\\/_/\\/____/ ";
	GotoXY(53, 22);
	cout << "MENU";
	GotoXY(47, 25);
	SetColor(6, 0);
	cout << ">> New Game ";
	SetColor(0, 6);
	GotoXY(51, 26);
	cout << "Load Game";
	GotoXY(51, 27);
	cout << "High Scores";
	GotoXY(51, 28);
	cout << "Credits";
	GotoXY(51, 29);
	cout << "Exit";
	SetColor(0, 7);
}
int screen::displayMove(int& x, int& y, char key) {
	sndPlaySound(TEXT("./SoundTrack/SelectInMenu.wav"), SND_FILENAME | SND_ASYNC);
	if (key != 'W' && key != 'S') return y;
	int xc = x, yc = y;
	if (key == 'W' && y > 25) y--;
	else if (key == 'S' && y < 29) y++;

	GotoXY(xc, yc);
	SetColor(0, 6);
	if (yc == 25) cout << "    New Game";
	else if (yc == 26) cout << "    Load Game";
	else if (yc == 27) cout << "    High Scores";
	else if (yc == 28) cout << "    Credits";
	else if (yc == 29) cout << "    Exit";
	xc = x; yc = y;
	GotoXY(x, y);
	SetColor(6, 0);
	if (y == 25) cout << ">> New Game ";
	else if (y == 26) cout << ">> Load Game ";
	else if (y == 27) cout << ">> High Scores ";
	else if (y == 28) cout << ">> Credits ";
	else if (y == 29) cout << ">> Exit ";
	SetColor(0, 7);
	return y;
}
string screen::_inputNameScreen(int color) {
	system("cls");
	this->_printFrame(color);
	SetColor(0, color);
	GotoXY(6, 11);
	cout << " ______  ______  ______  ______  ______  __  __   __  ______       ______  ______  ______  _____   ";
	GotoXY(6, 12);
	cout << "/\\  ___\\/\\  == \\/\\  __ \\/\\  ___\\/\\  ___\\/\\ \\/\\ \"-.\\ \\/\\  ___\\     /\\  == \\/\\  __ \\/\\  __ \\/\\  __-. ";
	GotoXY(6, 13);
	cout << "\\ \\ \\___\\ \\  __<\\ \\ \\/\\ \\ \\___  \\ \\___  \\ \\ \\ \\ \\-.  \\ \\ \\__ \\    \\ \\  __<\\ \\ \\/\\ \\ \\  __ \\ \\ \\/\\ \\ ";
	GotoXY(6, 14);
	cout << " \\ \\_____\\ \\_\\ \\_\\ \\_____\\/\\_____\\/\\_____\\ \\_\\ \\_\\\\\"\\_\\ \\_____\\    \\ \\_\\ \\_\\ \\_____\\ \\_\\ \\_\\ \\____- ";
	GotoXY(6, 15);
	cout << "  \\/_____/\\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/\\/_/ \\/_/\\/_____/     \\/_/ /_/\\/_____/\\/_/\\/_/\\/____/ ";
	GotoXY(this->x + 40, this->y + 22);
	string name;
	SetColor(6, 0);
	cout << "Input your name: ";
	getline(cin, name);
	SetColor(0, 7);
	return name;
}
void screen::_printScoreMenu(int color, int Score, string PlayerName, int life, int level) {
	SetColor(0, 10);
	GotoXY(x + 6, y + 2);
	cout << "#     #                     ";
	GotoXY(x + 6, y + 3);
	cout << "##   ## ###### #    # #    #";
	GotoXY(x + 6, y + 4);
	cout << "# # # # #      ##   # #    #";
	GotoXY(x + 6, y + 5);
	cout << "#  #  # #####  # #  # #    #";
	GotoXY(x + 6, y + 6);
	cout << "#     # #      #  # # #    #";
	GotoXY(x + 6, y + 7);
	cout << "#     # #      #   ## #    #";
	GotoXY(x + 6, y + 8);
	cout << "#     # ###### #    #  #### ";
	SetColor(0, 6);
	GotoXY(x + 2, y + 10);
	cout << "Level: " << level;
	GotoXY(x + 2, y + 11);
	cout << "Player Name: " << PlayerName;
	GotoXY(x + 2, y + 12);
	cout << "Scores: " << Score;
	GotoXY(x + 2, y + 13);
	cout << "Lifes: " << life;
	GotoXY(x, y + 15);
	SetColor(0, 6);
	for (int i = x;i < z;i++) cout << (char)219;

	SetColor(0, 7);
	GotoXY(x + 2, y + 17);
	cout << "How to play:";
	GotoXY(x + 2, y + 18);
	cout << "- Use W A S D to move.";
	GotoXY(x + 2, y + 19);
	cout << "- Try not to hit cars or animals are";
	GotoXY(x + 2, y + 20);
	cout << "running on the road.";
	GotoXY(x + 2, y + 21);
	cout << "- When the signal light turns green";
	GotoXY(x + 2, y + 22);
	cout << "and yellow cars and animal may be";
	GotoXY(x + 2, y + 23);
	cout << "moving, but when it's red, they will ";
	GotoXY(x + 2, y + 24);
	cout << "stop.";
	GotoXY(x + 2, y + 25);
	cout << "- Press m to mute sound.";
	GotoXY(x + 2, y + 26);
	cout << "- Press b to save game.";
	GotoXY(x + 2, y + 27);
	cout << "- Press Esc to back to Menu.";
	GotoXY(x + 2, y + 28);
	cout << "You will recive nofication to ask save";
	GotoXY(x + 2, y + 29);
	cout << "game.";
	SetColor(0, 6);
	for (int i = x;i < z;i++) {
		GotoXY(i, y + 30);
		cout << (char)219;
	}

	SetColor(0, 7);
}
void screen::_loseScreen(int score) {
	this->_printFrame(6);
	SetColor(0, 4);
	GotoXY(x + 23, y + 15);
	cout << " __   __  _______  __   __    ___      _______  _______  _______ ";
	GotoXY(x + 23, y + 16);
	cout << "|  | |  ||       ||  | |  |  |   |    |       ||       ||       |";
	GotoXY(x + 23, y + 17);
	cout << "|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___|";
	GotoXY(x + 23, y + 18);
	cout << "|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ ";
	GotoXY(x + 23, y + 19);
	cout << "|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___|";
	GotoXY(x + 23, y + 20);
	cout << "  |   |  |       ||       |  |       ||       | _____| ||   |___ ";
	GotoXY(x + 23, y + 21);
	cout << "  |___|  |_______||_______|  |_______||_______||_______||_______|";
	SetColor(0, 2);
	GotoXY(x + 46, y + 24);
	cout << "Your scores is: " << score;
	GotoXY(x + 43, y + 25);
	cout << "Press any key to continue...";
	SetColor(0, 7);
}
void screen::_menuNofication(string a) {
	for (int i = x + 5;i < z;i++) {
		GotoXY(i, y + 35);
		cout << " ";
	}
	GotoXY(x + 5, y + 35);
	SetColor(0, 2);
	cout << a;
	SetColor(0, 7);
}
void screen::_ThanksForPlaying() {
	system("cls");
	cout << "Thanks For Playing...\n";
}
void screen::_printCredits(int color) {
	system("cls");
	this->_printFrame(color);
	SetColor(0, color);
	GotoXY(3, 8);
	cout << "  __    __   __    ______    ______   ______    __  __    ______    ______   __    ______    __   __    ";
	GotoXY(3, 9);
	cout << " /\\ \\  /\\ \"-.\\ \\  /\\  ___\\  /\\__  _\\ /\\  == \\  /\\ \\/\\ \\  /\\  ___\\  /\\__  _\\ /\\ \\  /\\  __ \\  /\\ \"-.\\ \\   ";
	GotoXY(3, 10);
	cout << " \\ \\ \\ \\ \\ \\-.  \\ \\ \\___  \\ \\/_/\\ \\/ \\ \\  __<  \\ \\ \\_\\ \\ \\ \\ \\____ \\/_/\\ \\/ \\ \\ \\ \\ \\ \\/\\ \\ \\ \\ \\-.  \\  ";
	GotoXY(48, 11);
	cout << "TEAM 5 - OOP";
	GotoXY(47, 12);
	cout << "CROSSING - ROAD";
	GotoXY(3, 13);
	cout << "    \\ \\_\\ \\ \\_\\\\\"\\_\\ \\/\\_____\\   \\ \\_\\  \\ \\_\\ \\_\\ \\ \\_____\\ \\ \\_____\\   \\ \\_\\  \\ \\_\\ \\ \\_____\\ \\ \\_\\\\\"\\_\\ ";
	GotoXY(3, 14);
	cout << "     \\/_/  \\/_/ \\/_/  \\/_____/    \\/_/   \\/_/ /_/  \\/_____/  \\/_____/    \\/_/   \\/_/  \\/_____/  \\/_/ \\/_/ ";
	GotoXY(36, 18);
	cout << "20127003 - HOANG QUOC BAO (LEADER " << char(4) << ")";
	GotoXY(36, 19);
	cout << "20127443 - NGUYEN HO HUU BANG (MEMBER)";
	GotoXY(36, 20);
	cout << "20127480 - NGUYEN TIEN DUY (MEMBER)";
	GotoXY(36, 21);
	cout << "20127531 - TRUONG TRONG KHANH (MEMBER)";
	GotoXY(36, 22);
	cout << "20127684 - MAI TRAN KHANH DUY (MEMBER)";
}
void screen::_printHowToPlay(int color) {
	system("cls");
	this->_printFrame(color);
	GotoXY(this->x + 49, y + 17);
	cout << "How to Play:";
	GotoXY(this->x + 10, y + 19);
	cout << "- Use W, A, S, D to move player.";
	GotoXY(this->x + 10, y + 20);
	cout << "- Try to don't hit animals or cars are running on the road.";
	GotoXY(this->x + 10, y + 21);
	cout << "- You have 3 lifes to play. Life will decrease by one everytime you hit the car or animal.";
	GotoXY(this->x + 10, y + 22);
	cout << "- Press b when playing game to save game.";
	GotoXY(this->x + 47, t - 2);
	cout << "CROSING ROAD GAME";
}
void screen::_levelScreen(int color) {
	system("cls");
	this->_printFrame(color);
	SetColor(0, color);
	GotoXY(6, 11);
	cout << " ______  ______  ______  ______  ______  __  __   __  ______       ______  ______  ______  _____   ";
	GotoXY(6, 12);
	cout << "/\\  ___\\/\\  == \\/\\  __ \\/\\  ___\\/\\  ___\\/\\ \\/\\ \"-.\\ \\/\\  ___\\     /\\  == \\/\\  __ \\/\\  __ \\/\\  __-. ";
	GotoXY(6, 13);
	cout << "\\ \\ \\___\\ \\  __<\\ \\ \\/\\ \\ \\___  \\ \\___  \\ \\ \\ \\ \\-.  \\ \\ \\__ \\    \\ \\  __<\\ \\ \\/\\ \\ \\  __ \\ \\ \\/\\ \\ ";
	GotoXY(6, 14);
	cout << " \\ \\_____\\ \\_\\ \\_\\ \\_____\\/\\_____\\/\\_____\\ \\_\\ \\_\\\\\"\\_\\ \\_____\\    \\ \\_\\ \\_\\ \\_____\\ \\_\\ \\_\\ \\____- ";
	GotoXY(6, 15);
	cout << "  \\/_____/\\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/\\/_/ \\/_/\\/_____/     \\/_/ /_/\\/_____/\\/_/\\/_/\\/____/ ";
	GotoXY(49, 22);
	cout << "CHOOSE LEVEL";
	GotoXY(48, 25);
	SetColor(6, 0);
	cout << ">> Easy ";
	SetColor(0, 6);
	GotoXY(52, 26);
	cout << "Normal";
	GotoXY(52, 27);
	cout << "Hard";
	SetColor(0, 7);
}
int screen::_chooseLevel(int& x, int& y, char key) {
	sndPlaySound(TEXT("./SoundTrack/SelectInMenu.wav"), SND_FILENAME | SND_ASYNC);
	if (key != 'W' && key != 'S') {
		if (y == 25) return 1;
		if (y == 26) return 11;
		if (y == 27) return 21;
	}
	int xc = x, yc = y;
	if (key == 'W' && y > 25) y--;
	else if (key == 'S' && y < 27) y++;
	GotoXY(xc, yc);
	SetColor(0, 6);
	if (yc == 25) cout << "    Easy";
	else if (yc == 26) cout << "    Normal";
	else if (yc == 27) cout << "    Hard";
	xc = x; yc = y;
	GotoXY(x, y);
	SetColor(6, 0);
	if (y == 25) cout << ">> Easy ";
	else if (y == 26) cout << ">> Normal ";
	else if (y == 27) cout << ">> Hard ";
	SetColor(0, 7);
	return 1;
}