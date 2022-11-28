#include <iostream>
#include <Windows.h>
#include "tronk.h"

using namespace std;

TriggerBot::TriggerBot() {
	INPUT self->input = initInput();
	HDC self->desktop = CreateDCA("DISPLAY", NULL, NULL, NULL);
	
	//pixel
	RECT rect;
	if(GetWindowRect(hwnd, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		
		int self->xPos = width / 2;
		int self->yPos = height / 2;
	}
}

void TriggerBot::activateBot() {
	COLORREF pixel;
	COLORREF startPixel;
	bool active = false;

	for (;;) {
		while (checkKeyDown) {
			if (!active) {
				startPixel = GetPixel(desktop, xPos, yPos);
				active = true;
			} else {
				if (startPixel != GetPixel(desktop, xPos, yPos) {
					click();
					while (startPixel != GetPixel(desktop, xPos, yPos) {
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
