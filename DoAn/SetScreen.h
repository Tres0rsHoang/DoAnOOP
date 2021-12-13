#ifndef SETSCREEN_H_
#define SETSCREEN_H_

#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

class screen {
	int x, y;
	int z, t;
public:
	screen(int x, int y, int z, int t) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->t = t;
	}
	screen() {
		this->x = this->y = this->z = this->t = 0;
	}

	//Chỉnh size màn hình
	void SetWindowSize(SHORT width, SHORT height) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT WindowSize;
		WindowSize.Top = 0;
		WindowSize.Left = 0;
		WindowSize.Right = width;
		WindowSize.Bottom = height;
		SetConsoleWindowInfo(hStdout, 1, &WindowSize);
	}
	//Khóa size màn hình
	void FixConsoleWindow() {
		HWND consoleWindow = GetConsoleWindow();
		LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
		style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
		style &= ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX); //tắt phòng to nhỏ
		SetWindowLong(consoleWindow, GWL_STYLE, style);
	}
	//Di chuyển điểm trên màn hình
	void GotoXY(int x, int y) {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	//Tắt tô chọn trong console
	void DisableSelection() {
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
	}
	//Chỉnh màu trong console
	void SetColor(int backgound_color, int text_color) {
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
	//Chỉnh vị trí nhìn trong console
	void SetScreenBufferSize(SHORT width, SHORT height) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD NewSize;
		NewSize.X = width;
		NewSize.Y = height;
		SetConsoleScreenBufferSize(hStdout, NewSize);
	}
	//Tắt con trỏ chuột trong console
	void ShowCur(bool CursorVisibility) {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO ConCurInf;

		ConCurInf.dwSize = 10;
		ConCurInf.bVisible = CursorVisibility;

		SetConsoleCursorInfo(handle, &ConCurInf);
	}

	void _input(int x, int y, int z, int t) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->t = t;
	}
	void _format() {
		system("cls");
		SetWindowSize(this->z, this->t);
		SetScreenBufferSize(this->z + 1, this->t + 1);
		FixConsoleWindow();
		ShowCur(0);
		//DisableSelection();
	}
	int* _getinform() {
		int* result = new int[4];
		result[0] = this->x;
		result[1] = this->y;
		result[2] = this->z;
		result[3] = this->t;
		return result;
	}

	//In khuôn trò chơi
	void _printFrame(int color) {
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
	void _printLightFrame(int color) {
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
	void _printDisplay(int color) {
		SetColor(0, color);
		GotoXY(5, 11);
		cout << " ______  ______  ______  ______  ______  __  __   __  ______       ______  ______  ______  _____   ";
		GotoXY(5, 12);
		cout << "/\\  ___\\/\\  == \\/\\  __ \\/\\  ___\\/\\  ___\\/\\ \\/\\ \"-.\\ \\/\\  ___\\     /\\  == \\/\\  __ \\/\\  __ \\/\\  __-. ";
		GotoXY(5, 13);
		cout << "\\ \\ \\___\\ \\  __<\\ \\ \\/\\ \\ \\___  \\ \\___  \\ \\ \\ \\ \\-.  \\ \\ \\__ \\    \\ \\  __<\\ \\ \\/\\ \\ \\  __ \\ \\ \\/\\ \\ ";
		GotoXY(5, 14);
		cout << " \\ \\_____\\ \\_\\ \\_\\ \\_____\\/\\_____\\/\\_____\\ \\_\\ \\_\\\\\"\\_\\ \\_____\\    \\ \\_\\ \\_\\ \\_____\\ \\_\\ \\_\\ \\____- ";
		GotoXY(5, 15);
		cout << "  \\/_____/\\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/\\/_/ \\/_/\\/_____/     \\/_/ /_/\\/_____/\\/_/\\/_/\\/____/ ";
		GotoXY(53, 22);
		cout << "MENU";
		GotoXY(47, 25);
		SetColor(15, 6);
		cout << ">> New Game ";
		SetColor(0, 6);
		GotoXY(51, 26);
		cout << "Load Game";
		GotoXY(51, 27);
		cout << "High Scores";
		GotoXY(51, 28);
		cout << "Intruction";
		GotoXY(51, 29);
		cout << "Exit";
		SetColor(0, 7);
	}
	int displayMove(int &x, int &y, char key) {
		if (key != 'W' && key != 'S') return y;
		int xc = x, yc = y;
		if (key == 'W' && y > 25) y--;
		else if (key == 'S' && y < 29) y++;

		GotoXY(xc, yc);
		SetColor(0, 6);
		if (yc == 25) cout << "    New Game";
		else if (yc == 26) cout << "    Load Game";
		else if (yc == 27) cout << "    High Scores";
		else if (yc == 28) cout << "    Intruction";
		else if (yc == 29) cout << "    Exit";
		xc = x; yc = y;
		GotoXY(x, y);
		SetColor(15, 6);
		if (y == 25) cout << ">> New Game ";
		else if (y == 26) cout << ">> Load Game ";
		else if (y == 27) cout << ">> High Scores ";
		else if (y == 28) cout << ">> Intruction ";
		else if (y == 29) cout << ">> Exit ";
		SetColor(0, 7);
		return y;
	}
	string _inputNameScreen(int color) {
		string name;
		this->_printFrame(color);
		SetColor(15, 6);
		GotoXY((x + z) / 2 - 16, (y + t) / 2);
		cout << "Input your name: ";
		getline(cin, name);
		SetColor(0, 7);
		return name;
	}
	void _printScoreMenu(int color, int Score, string PlayerName, int life, int level) {
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
		cout<<"running on the road.";
		GotoXY(x + 2, y + 21);
		cout << "- When the signal light turns green";
		GotoXY(x + 2, y + 22);
		cout<<"and yellow cars and animal may be";
		GotoXY(x + 2, y + 23);
		cout << "moving, but when it's red, they will ";
		GotoXY(x + 2, y + 24);
		cout<<"stop.";
		GotoXY(x + 2, y + 25);
		cout << "- Press b to save game.";
	}
	void _loseScreen(int score) {
		this->_printFrame(6);
		SetColor(0, 4);
		GotoXY(x+25, y + 15);
		cout << " __   __  _______  __   __    ___      _______  _______  _______ ";
		GotoXY(x+25, y + 16);
		cout << "|  | |  ||       ||  | |  |  |   |    |       ||       ||       |";
		GotoXY(x+25, y + 17);
		cout << "|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___|";
		GotoXY(x+25, y + 18);
		cout << "|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ ";
		GotoXY(x+25, y + 19);
		cout << "|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___|";
		GotoXY(x+25, y + 20);
		cout << "  |   |  |       ||       |  |       ||       | _____| ||   |___ ";
		GotoXY(x+25, y + 21);
		cout << "  |___|  |_______||_______|  |_______||_______||_______||_______|";
		GotoXY(x + 55, y + 22);
		cout << "Your scores is: " << score;
		GotoXY(x + 45, y + 23);
		cout << "Press any key to continue...";
		system("pause > nul");
		SetColor(0, 7);
	}
	
};

#endif


