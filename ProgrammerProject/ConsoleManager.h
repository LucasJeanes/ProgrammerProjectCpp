#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <windows.h>

class ConsoleManager {
public:
	void CursorColour(const int&);
	void GotoXY(const int&, const int&);
	void HideCursor();
	void SetConsoleSize(const BOOL&, const int&, const int&);
private:

};

#endif