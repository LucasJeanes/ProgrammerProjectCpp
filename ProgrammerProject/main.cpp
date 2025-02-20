/*
 `....
`..   `..   `..      `..
`..         `..      `..
`..     `...`.....`...`.....
`..         `..      `..
`..   `..   `..      `..
 `....

Lucas Jeanes
(Credits to Michelle Lynch for above ASCII art)
*/

#include <iostream>		    // cerr, endl
#include <stdexcept>	    // out_of_range
#include <random>
#include <thread>
#include <mutex>
#include <windows.h>

#include "ConsoleManager.h"
#include "Programmer.h"		// Programmer
#include "TestProgrammer.h"	// Test functions
#include "RainEffect.h"

std::mutex printMutex;

int main(int argc, char** argv)
{
	int rainCount = 100000;
	const int rainLength = 29;
	const int maxWindowCharX = 100;
	const int trailLengthVal = 20;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> rainPrintWidth(0, maxWindowCharX);
	std::uniform_int_distribution<> trailLength(10, trailLengthVal);
	std::uniform_int_distribution<> heaviness(1, 40);
	std::uniform_int_distribution<> speed(10, 100);


	try {
		ConsoleManager consoleManager;
		consoleManager.HideCursor();
		consoleManager.SetConsoleSize(true, maxWindowCharX, rainLength);

		std::vector<std::thread> threads;

		for (int i = 0; i < rainCount; i++) {
			threads.emplace_back(std::thread(RainEffect, rainPrintWidth(gen), rainLength, trailLength(gen), speed(gen)));
			Sleep(heaviness(gen));
		}

		for (auto& t : threads)
			t.join();
	}
	catch (std::out_of_range& e) {
		std::cerr << std::endl << e.what() << std::endl;
		return -1;
	}
	return 0;
}
