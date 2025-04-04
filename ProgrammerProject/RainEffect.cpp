 #include "RainEffect.h"
#include <windows.h>
#include <iostream>
#include <mutex>
#include "ConsoleManager.h"

extern std::mutex printMutex;

void RainEffect(int rowX, int columnY, const int& trailLength, const int& speed, const int& rainColour, const int& trailColour) {
	ConsoleManager consoleManager;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(32, 126);

		for (int y = 0; y < columnY; y++) {
			char randomChar = static_cast<char>(distrib(gen));
			{
				std::lock_guard<std::mutex> guard(printMutex);
				consoleManager.GotoXY(rowX, y);
				if (y == columnY - 1) { 
					consoleManager.CursorColour(trailColour); //10 green colour for last character
				}
				else {
					consoleManager.CursorColour(rainColour); //15 white for current character
				}
				std::cout << static_cast<char>(distrib(gen));
			}

			if (y > 0) { //Sets previous character to green
				{
					std::lock_guard<std::mutex> guard(printMutex);
					consoleManager.GotoXY(rowX, y - 1);
					consoleManager.CursorColour(trailColour); //green character reprint
					std::cout << randomChar;
				}
			}
			{
				std::lock_guard<std::mutex> guard(printMutex);
				consoleManager.GotoXY(rowX, y - trailLength);
				std::cout << " "; //whitespace to "remove" character
			}
			Sleep(speed);
		}
		for (int y = columnY - trailLength; y <= columnY; y++) { //Replace old sequence with whitespace
			{
				std::lock_guard<std::mutex> guard(printMutex);
				consoleManager.GotoXY(rowX, y);
				std::cout << " "; //whitespace to "remove" character
			}
			Sleep(speed);
			std::this_thread::yield();
		}
}
