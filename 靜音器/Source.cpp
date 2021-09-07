#include<iostream>
#include<vector>
#include<memory.h>
#include<cmath>
#include<set>
#include<map>
#include<algorithm>
#include<numeric>
#include<string>
#include<array>
#include<fstream>
#include <windows.h>
#include<ctime>
using namespace std;

#define ll long long 
#define ar array
DWORD k = 50;
bool play = false;
int mode1 = 2;
vector<int> tt = { 1000, 1000, 1000, 1000, 1000 };
int keyboard_delay = 0;
int main() {
	clock_t t1;
	t1 = clock();
	int mode1_size = tt.size();
	int toggle1 = 1;
	cout << "暫停中...\n";
	while (true) {
		if (GetAsyncKeyState(VK_LCONTROL)) {
			if (GetAsyncKeyState(VK_SPACE) == -32767) {
				play = !play;
				string str = play ? "Start" : "Pause";
				cout << str << endl;
			}
		}
		if ((GetAsyncKeyState(VK_NUMPAD0) == -32767 || GetAsyncKeyState(0x5A) == -32767) && play) {
			cout << "按下左鍵...\n";
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		else if ((GetAsyncKeyState(VK_NUMPAD9) == -32767 || GetAsyncKeyState(0x43) == -32767 )&& play) {
			cout << "按下右鍵...\n";
			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		}
		else if ((GetAsyncKeyState(VK_NUMPAD1) == -32767 || GetAsyncKeyState(0x58) == -32767) && play) {
			if (toggle1) {
				cout << "按下左鍵...\n";
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			}
			else {
				cout << "放開左鍵...\n";
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			toggle1 = !toggle1;
		}
		if ((clock() - t1 >= tt[mode1]) && play) {
			cout << "持續運作中..." << double(tt[mode1]) / 1000 << "s 提醒器..." << endl;
			Sleep(keyboard_delay);
			t1 = clock() + int(k) + keyboard_delay;
		}
		Sleep(k);
	}
	return 0;
}