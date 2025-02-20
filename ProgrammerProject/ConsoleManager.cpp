#include <windows.h>
#include "ConsoleManager.h"
#include <string>


void ConsoleManager::HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void ConsoleManager::SetConsoleSize(const BOOL& sizeOverride, const int& maxCharX, const int& maxCharY) {
	std::string systemMode = "mode ";
	systemMode += std::to_string(maxCharX+1) + "," + std::to_string(maxCharY+1);
	system(systemMode.c_str()); // Create system string ("mode x,y") based on user input = X and Y is the dimension size of the window buffer

	HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT newWindow = {0, 0, maxCharX+1, maxCharY+1};
	SMALL_RECT* winSize = &newWindow;

	SetConsoleWindowInfo(cHandle, sizeOverride, winSize);
}

void ConsoleManager::CursorColour(const int& colour) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, colour);
}

void ConsoleManager::GotoXY(const int& x, const int& y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
