#include <iostream>
#include <Windows.h>
#include "tronk.h"

using namespace std;

TriggerBot::TriggerBot() {
	this->desktop = CreateDCA("DISPLAY", NULL, NULL, NULL);
	
	this->input[0].type = INPUT_MOUSE;
	this->input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	this->input[1].type = INPUT_MOUSE;
	this->input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	
	//pixel
	RECT rect;
	const HWND hDesktop = GetDesktopWindow();
	if(GetWindowRect(hDesktop, &rect)) {
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
	cout << "Active\n";

	for (;;) {
		active = false;
		while (checkKeyDown(0x54)) {
			if (!active) {
				startPixel = GetPixel(this->desktop, this->xPos, this->yPos);
				active = true;
			} else {
				if (startPixel != GetPixel(this->desktop, this->xPos, this->yPos)) {
					cout << "click\n";
					click(this->input);
					while (startPixel != GetPixel(this->desktop, this->xPos, this->yPos)) {	}
				}
			}
		}
	}
}

bool TriggerBot::checkKeyDown(int key) {
	return GetAsyncKeyState(key);
}

void TriggerBot::click(INPUT Inputs[]) {
	SendInput(2, Inputs, sizeof(INPUT));
}