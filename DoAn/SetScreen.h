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
	screen(int x, int y, int z, int t);
	screen();

	//Chỉnh size màn hình
	void SetWindowSize(SHORT width, SHORT height);
	//Khóa size màn hình
	void FixConsoleWindow();
	//Di chuyển điểm trên màn hình
	void GotoXY(int x, int y);
	//Tắt tô chọn trong console
	void DisableSelection();
	//Chỉnh màu trong console
	void SetColor(int backgound_color, int text_color);
	//Chỉnh vị trí nhìn trong console
	void SetScreenBufferSize(SHORT width, SHORT height);
	//Tắt con trỏ chuột trong console
	void ShowCur(bool CursorVisibility);

	void _input(int x, int y, int z, int t);
	void _format();
	int* _getinform();

	//In khuôn trò chơi
	void _printFrame(int color);
	void _printLightFrame(int color);
	void _printDisplay(int color);
	int displayMove(int& x, int& y, char key);
	string _inputNameScreen(int color);
	void _printScoreMenu(int color, int Score, string PlayerName, int life, int level);
	void _loseScreen(int score);
	void _menuNofication(string a);
	void _ThanksForPlaying();
	void _printCredits(int color);
	void _printHowToPlay(int color);
	void _levelScreen(int color);
	int _chooseLevel(int& x, int& y, char key);
};

#endif


