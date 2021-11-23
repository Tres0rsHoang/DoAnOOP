#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cwchar>

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
	void _displayscreen(char key) {

	}
};



