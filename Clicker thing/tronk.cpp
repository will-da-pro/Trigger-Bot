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
	INPUT ip;

	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
	ip.mi.mouseData = 0;
	ip.mi.dwExtraInfo = NULL;
	ip.mi.time = 0;

	return ip;
}

void TriggerBot::click(INPUT ip) {
	SendInput(1, &ip, sizeof(ip));
}
