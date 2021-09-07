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
vector<int> tt = { 1500, 1000, 700, 500, 370 };
int keyboard_delay = 0;
int main() {
	clock_t t1;
	t1 = clock();
	int lclick = 0;
	int mode1_size = tt.size();
	cout << "暫停中...";
	while (true) {
		if (GetAsyncKeyState(VK_LCONTROL)) {
			if (GetAsyncKeyState(VK_SPACE) == -32767) {
				cout << "切換速度" << endl;
				++mode1;
				mode1 %= mode1_size;
			}
			else if (GetAsyncKeyState(0x56) == -32767) {
				play = !play;
				string str = play ? "resume" : "pause";
				cout << str << endl;
			}
		}
		if (GetAsyncKeyState(VK_LBUTTON) == -32767 && play) {
			cout << "按下左鍵...等待5s中\n";
			lclick = 5000;
			t1 = clock();
		}
		if (GetAsyncKeyState(VK_RBUTTON) == -32767 && play) {
			cout << "按下右鍵...解除等待\n";
			lclick = 0;
		}
		if ((clock() - t1 >= tt[mode1] && clock() - t1 >= lclick) && play) {
			if (lclick != 0)cout << "結束等待\n";
			lclick = 0;
			cout << "現在速度:" << double(tt[mode1]) / 1000 << "s" << endl;
			keybd_event(VK_RIGHT, 0x27, 0, 0);
			keybd_event(VK_RIGHT, 0x27, KEYEVENTF_KEYUP, 0);
			Sleep(keyboard_delay);
			t1 = clock() + int(k) + keyboard_delay;
		}
		Sleep(k);
	}
	return 0;
}