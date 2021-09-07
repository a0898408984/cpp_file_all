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
#include<queue>
using namespace std;
using std::cout;
#define ll long long 
#define ar array
vector<vector<int> > game_map;
int m = 25;
int n = 40;
DWORD k = 10;
bool play = false;
bool gameover = false;
int init_long = 20;
const int init_speed = 110;
string fruit_icon = "☆";
string snake_headicon = "◎";
string snake_bodyicon = "●" ;
string wall = "□";
struct snack {
	int l = init_long;
	int speed = init_speed;
	char dir = 'r';
	int point = 0;
	vector<vector<int>> body;
	vector<int> fruit;
}s;
void gotoxy(int x, int y){
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = x;     // defining x-axis
	coordinates.Y = y;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void game_pause(string str) {
	gotoxy(2 * (n + 2 + 2), 4);
	str = str == "" ? "　　　　　　　　　　" : str;
	cout << str;
}
void change_coord(int i, int j) {
	gotoxy(2 * (n + 2 + 2), 6);
	cout << "Coord: (" << i << ", " << j << ")   ";
}
void change_snakelong() {
	gotoxy(2 * (n + 2 + 2), 8);
	cout << "Snake_long: "  << s.l << "   ";
}
void change_speed() {
	gotoxy(2 * (n + 2 + 2), 10);
	cout << "Snake_speed: " << s.speed << "   ";
}
void change_dir() {
	gotoxy(2 * (n + 2 + 2), 12);
	cout << "Snake_dir: " << s.dir << "   ";
}
void change_point() {
	gotoxy(2 * (n + 2 + 2), 14);
	cout << "Game_point: " << s.point<< "   ";
}
void change_log1(string str) {
	gotoxy(2 * (n + 2 + 2), 16);
	cout << "                         ";
	gotoxy(2 * (n + 2 + 2), 16);
	cout << str;
}
void draw_dir() {
	change_dir();
	auto fruit = s.fruit;
	auto it_tail = s.body[0];
	auto it_head = s.body[s.body.size()-1];
	vector<int> tmp = { it_head[0],it_head[1] };
	if (s.dir == 'r')tmp[0]++;
	else if (s.dir == 'l') tmp[0]--;
	else if (s.dir == 'u') tmp[1]--;
	else if (s.dir == 'd') tmp[1]++;
	gotoxy(it_head[0] * 2, it_head[1]);
	cout << snake_bodyicon ;
	gotoxy(tmp[0] * 2, tmp[1]);
	cout << snake_headicon;
	gotoxy(it_tail[0] * 2, it_tail[1]);
	if (s.fruit[0] != tmp[0] || s.fruit[1] != tmp[1]) {
		s.body.erase(s.body.begin());
		cout << "　";
	}
	s.body.push_back(tmp);
	auto coord = s.body[s.body.size() - 1];
	change_coord(coord[0], coord[1]);
	change_snakelong();
	change_speed();
	change_point();
	change_dir();
}

void init() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	for (int i = 0; i < m; ++i) {
		vector<int> tmp;
		for (int j = 0; j < n; ++j) {
			tmp.push_back(0);
		}
		game_map.push_back(tmp);
	}
	for (int i = 0; i < n + 2; ++i)
		cout << wall;
	gotoxy(0, m + 1);
	for (int i = 0; i < n + 2; ++i)
		cout << wall;
	for (int i = 1; i < m + 1; ++i) {
		gotoxy(0, i);
		cout << wall;
		gotoxy(2 * (n + 1), i);
		cout << wall;
	}

	
	int max_n = n - 6;
	int max_m = m - 3;
	int n1 = s.l / max_n;
	n1 = n1 >= max_m ? max_m : n1;
	int n2 = s.l - n1*max_n;
	n2 = n2 >= max_n ? max_n : n2;
	s.l = n1 * max_n + n2;
	bool go_r = false;
	//change_log1(to_string(n1) +","+ to_string(n2) + "," + to_string(max_m) + "," + to_string(max_n));
	int x = 4, y = 1;
	for (int i = 0; i < n1 + 1; ++i) {
		go_r = !go_r;
		if (i != n1) {
			for (int j = 0; j < max_n; ++j) {
				if (j == 0) {
					++y;
				}
				else {
					if (go_r) {
						++x;
					}
					else {
						--x;
					}
				}
				gotoxy(x * 2, y);
				cout << snake_bodyicon ;
				s.body.push_back({ x, y });
			}
		}
		else {
			for (int j = 0; j < n2; ++j) {
				if (j == 0) {
					++y;
				}
				else {
					if (go_r) {
						++x;
					}
					else {
						--x;
					}
				}
				gotoxy(x * 2, y);
				cout << snake_bodyicon ;
				s.body.push_back({ x, y });
			}
		}
	}
	if (go_r)s.dir = 'r';
	else s.dir = 'l';
	gotoxy(x * 2, y);
	cout << snake_headicon;
	s.body.push_back({ x, y });
	game_pause("等待開始中..");
	auto coord = s.body[s.body.size() - 1];
	change_coord(coord[0], coord[1]);
	change_snakelong();
	change_speed();
	change_point();
	change_dir();
	s.fruit.push_back(2);
	s.fruit.push_back(m/2);
	gotoxy(s.fruit[0] * 2, s.fruit[1]);
	cout << fruit_icon;
}
void replay() {
	gameover = false;
	system("cls");
	s.body = {};
	s.l = init_long;
	s.speed = init_speed;
	s.point = 0;
	s.fruit = {};
	init();
}

void game_end() {
	vector<int> tmp_s0 = s.body[0];
	s.body[0] = { -1,-1 };
	vector<int> tmp = s.body[s.body.size() - 1];
	if (s.dir == 'r')tmp[0]++;
	else if (s.dir == 'l') tmp[0]--;
	else if (s.dir == 'u') tmp[1]--;
	else if (s.dir == 'd') tmp[1]++;
	if (tmp[0] == 0 || tmp[0] == n + 1 || tmp[1] == 0 || tmp[1] == m + 1) {
		gameover = true;
		return;
	}
	int count = 0;
	for (auto x : s.body) {
		if (x[0] == tmp[0] &&
			x[1] == tmp[1]) {
			gameover = true;
			return;
		}
	}
	s.body[0] = tmp_s0;
}
int randomInt(int p, int q) {
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<int> dis(p,q);
	//return dis(gen);
	static int init = 0;
	if (init == 0) { srand((unsigned)time(NULL)), rand(), ++init; }
	return (int)((rand() / (RAND_MAX + 1.0)) * (q - p + 1.0) + p);
}
void eat_fruit() {
	vector<int> tmp = s.body[s.body.size() - 1];
	if (s.fruit[0] == tmp[0] && s.fruit[1] == tmp[1]) {
		s.l++;
		vector<vector<int> > fruittmp;
		vector<vector<int> > select;
		for (int i = 1; i < m + 1; ++i) {
			for (int j = 1; j < n + 1; ++j) {
				fruittmp.push_back({ j, i });
			}
		}
		for (auto x : s.body) {
			int num = x[0] + (x[1] - 1 ) * n - 1;
			fruittmp[num] = { -1,-1 };
		}
		for (auto x : fruittmp) {
			if (x[0] != -1 && x[1] != -1) {
				select.push_back(x);
			}
		}
		int num = randomInt(0, select.size() - 1);
		s.fruit[0] = select[num][0];
		s.fruit[1] = select[num][1];
		s.point += s.l * 100;
		gotoxy(s.fruit[0] * 2, s.fruit[1]);
		cout << fruit_icon;
		if (s.point > 10000 && s.point <= 20000) { s.speed = 100; }
		else if (s.point > 20000 && s.point <= 40000) { s.speed = 90; }
		else if (s.point > 40000 && s.point <= 70000) { s.speed = 80; }
		else if (s.point > 70000 && s.point <= 100000) { s.speed = 70; }
		else if (s.point > 100000 && s.point <= 150000) { s.speed = 60; }
		else if (s.point > 150000 && s.point <= 200000) { s.speed = 50; }
		else if (s.point > 200000 && s.point <= 300000) { s.speed = 40; }
		else if (s.point > 300000 && s.point <= 20000000) { s.speed = 35; }
		change_speed();
	}
}



int main() {
	cout << "input map_size mxN and snake_size l (10 < m < 25, 10 < n < 40 , 10 < l)";
	cout << "m, n, l = ";
	cin >> m >> n >> s.l;
	init_long = s.l;
	if (m < 10) m = 10;
	else if (m > 50)m = 50;
	if (n < 10) n = 10;
	else if (n > 80)m = 80;
	system("cls");
	init();
	clock_t t1;
	t1 = clock();
	char tmp_dir = 'x';
	while(true){
		if (GetAsyncKeyState(VK_LCONTROL)) {
			if (GetAsyncKeyState(VK_SPACE) == -32767) {
				if (gameover) 
					replay();
				play = !play;
				string str = play ? "" : "PAUSE";
				game_pause(str);
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) == -32767 && s.dir != 'l' && s.dir != 'r') {
			tmp_dir = 'r';
		}
		else if (GetAsyncKeyState(VK_LEFT) == -32767 && s.dir != 'l' && s.dir != 'r') {
			tmp_dir = 'l';
		}
		else if (GetAsyncKeyState(VK_UP) == -32767 && s.dir != 'u' && s.dir != 'd') {
			tmp_dir = 'u';
		}
		else if (GetAsyncKeyState(VK_DOWN) == -32767 && s.dir != 'u' && s.dir != 'd') {
			tmp_dir = 'd';
		}
		Sleep(k);
		if (clock()-t1 > s.speed && play) {
			s.dir = tmp_dir == 'x'? s.dir:tmp_dir;
			game_end();
			if (!gameover) {
				draw_dir();
				eat_fruit();
				tmp_dir = 'x';
				t1 = clock();
			}
		}
		if (gameover&& play) {
			game_pause("遊戲結束..再來一局？");
			play = !play;
		}
	}

	return 0;
}