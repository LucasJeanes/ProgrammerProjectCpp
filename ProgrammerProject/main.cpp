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
#include "StartupScript.h"
#include "ConsoleManager.h"
#include "RainEffect.h"

std::mutex printMutex;

int main(int argc, char** argv)
{
	try {
		ConsoleManager consoleManager;
		consoleManager.HideCursor();
		StartupScript startupScript;
		startupScript.WelcomeMsg(consoleManager);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> rainPrintWidth(0, startupScript.GetMaxWindowCharX());	//Width of rain print
		std::uniform_int_distribution<> trailLength(10, startupScript.GetTrailLengthVal());	//Length of rain trail
		std::uniform_int_distribution<> heaviness(1, startupScript.GetHeaviness());	//Delay between raindrops
		std::uniform_int_distribution<> speed(10, startupScript.GetMaxSpeed());		//Speed of raindrops

		consoleManager.SetConsoleSize(true, startupScript.GetMaxWindowCharX(), startupScript.GetMaxWindowCharY());

		std::vector<std::thread> threads;

		for (int i = 0; i < startupScript.GetRainCount(); i++) {
			threads.emplace_back(std::thread(RainEffect, 
				rainPrintWidth(gen), 
				startupScript.GetMaxWindowCharY(), 
				trailLength(gen), speed(gen), 
				startupScript.GetRainColour(), 
				startupScript.GetTrailColour()));
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
