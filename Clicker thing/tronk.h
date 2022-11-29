#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class TriggerBot {
public:
	TriggerBot();
	void activateBot();
private:
	HDC desktop;
	INPUT input[2];
	int xPos;
	int yPos;
	
	bool checkKeyDown(int key);
	INPUT initInput();
	void click(INPUT ip);
};
