#include <iostream>
#include <Windows.h>
#include "tronk.h"

using namespace std;

TriggerBot::TriggerBot() {
	this->input = initInput();
	this->desktop = CreateDCA("DISPLAY", NULL, NULL, NULL);
	
	//pixel
	RECT rect;
	if(GetWindowRect(hwnd, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		
		this->xPos = width / 2;
		this->yPos = height / 2;
	}
}

void TriggerBot::activateBot() {
	COLORREF pixel;
	COLORREF startPixel;
	bool active = false;

	for (;;) {
		active = false;
		while (checkKeyDown(0x50)) {
			if (!active) {
				startPixel = GetPixel(this->desktop, this->xPos, this->yPos);
				active = true;
			} else {
				if (startPixel != GetPixel(this->desktop, this->xPos, this->yPos) {
					click(this->input);
					while (startPixel != GetPixel(this->desktop, this->xPos, this->yPos) {
						sleep(0.01);
					}
				}
			}
		}
	}
}

bool TriggerBot::checkKeyDown(int key) {
	return GetAsyncKeyState(key);
}

INPUT TriggerBot::initInput() {
	INPUT Inputs[2] = {0};
	
	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	Inputs[1].type = INPUT_MOUSE;
	Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	return Inputs;
}

void TriggerBot::click(INPUT Inputs) {
	SendInput(2, Inputs, sizeof(INPUT));
}
