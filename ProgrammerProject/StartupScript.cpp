#include "StartupScript.h"

StartupScript::StartupScript() {

}
StartupScript::StartupScript(int rainCount, int maxWindowCharX, int maxWindowCharY, int trailLengthVal, int maxSpeed, int heaviness) : 
	rainCount_{ rainCount }, maxWindowCharX_{ maxWindowCharX }, maxWindowCharY_{ maxWindowCharY }, trailLengthVal_{ trailLengthVal }, maxSpeed_{ maxSpeed }, heaviness_{ heaviness }
{
#if VERBOSE
	std::cout << "Programmer all-arg constructor" << std::endl;
#endif
}

static void PrintColourLine(ConsoleManager& console, int colourCode, const std::string& label) {
	std::cout << "  " << colourCode << " = ";
	console.CursorColour(colourCode);
	std::cout << label;
	console.CursorColour(15); // reset to white
	std::cout << std::endl;
}

void StartupScript::WelcomeMsg(ConsoleManager& console) {
	std::cout << "Welcome to the Digital Rain!" << std::endl;
	std::cout << "Enter 0 to load defaults." << std::endl;
	std::cout << "Number of raindrops (e.g. 10,000): ";
	std::cin >> rainCount_;
	if (rainCount_ == 0) 
	{
		DefaultValues();
	}
	else 
	{
		std::cout << "Max length of rain drop (e.g. 20): ";
		std::cin >> trailLengthVal_;

		std::cout << "Window width (e.g. 100): ";
		std::cin >> maxWindowCharX_;

		std::cout << "Window height (e.g. 29): ";
		std::cin >> maxWindowCharY_;

		std::cout << "Maximum speed (e.g. 100): ";
		std::cin >> maxSpeed_;

		std::cout << "Heaviness (delay between drops in ms, e.g. 40): ";
		std::cin >> heaviness_;

		std::cout << "\nColour reference (Windows console colours):\n";
		PrintColourLine(console, 0, "Black");
		PrintColourLine(console, 1, "Blue");
		PrintColourLine(console, 2, "Green");
		PrintColourLine(console, 3, "Aqua");
		PrintColourLine(console, 4, "Red");
		PrintColourLine(console, 5, "Purple");
		PrintColourLine(console, 6, "Yellow");
		PrintColourLine(console, 7, "White");
		PrintColourLine(console, 8, "Gray");
		PrintColourLine(console, 9, "Light Blue");
		PrintColourLine(console, 10, "Light Green");
		PrintColourLine(console, 11, "Light Aqua");
		PrintColourLine(console, 12, "Light Red");
		PrintColourLine(console, 13, "Light Purple");
		PrintColourLine(console, 14, "Light Yellow");
		PrintColourLine(console, 15, "Bright White");
		std::cout << std::endl;

		std::cout << "Rain drop colour (0 to 15, default 15 = white): ";
		std::cin >> rainColour_;

		std::cout << "Trail colour (0 to 15, default 10 = green): ";
		std::cin >> trailColour_;
	}
}

void StartupScript::DefaultValues()
{
	rainCount_ = 100000;
	maxWindowCharY_ = 29;
	maxWindowCharX_ = 100;
	trailLengthVal_ = 20;
	maxSpeed_ = 100;
	heaviness_ = 40;
	rainColour_ = 15;
	trailColour_ = 10;
}

int StartupScript::GetRainCount() { return rainCount_; }
int StartupScript::GetTrailLengthVal(){ return trailLengthVal_; }
int StartupScript::GetMaxWindowCharX(){ return maxWindowCharX_; }
int StartupScript::GetMaxWindowCharY() { return maxWindowCharY_; }
int StartupScript::GetMaxSpeed() { return maxSpeed_; }
int StartupScript::GetHeaviness() { return heaviness_; }
int StartupScript::GetRainColour() { return rainColour_; }
int StartupScript::GetTrailColour() { return trailColour_; }
