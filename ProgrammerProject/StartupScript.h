#ifndef STARTUPSCRIPT_H
#define STARTUPSCRIPT_H

#include <iostream>
#include "ConsoleManager.h"


class StartupScript {

public:
	void WelcomeMsg(ConsoleManager& console);
	StartupScript();
	StartupScript(int, int, int, int, int , int);
	void DefaultValues();
	int GetRainCount();
	int GetTrailLengthVal();
	int GetMaxWindowCharX();
	int GetMaxWindowCharY();
	int GetMaxSpeed();
	int GetHeaviness();
	int GetRainColour();
	int GetTrailColour();

private:
	int rainCount_;		//No. of raindrops (determines runtime)
	int maxWindowCharY_;	//vertical character window size
	int maxWindowCharX_;	//horizontal character window size
	int trailLengthVal_;	//length of rain trail
	int maxSpeed_;
	int heaviness_;
	int rainColour_;
	int trailColour_;
	};

#endif
