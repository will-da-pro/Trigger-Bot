#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class TriggerBot {
public:
	void activateBot();
private:
	bool checkKeyDown(int key);
	INPUT initInput();
	void click(INPUT ip);
	COLORREF getPixelValue(HDC display);
};