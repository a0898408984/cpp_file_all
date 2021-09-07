#include<set>
#include<map>
#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include<ctime>
using namespace std;

#define ll long long 
#define ar array
int randomInt(int p, int q) {
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<int> dis(p,q);
	//return dis(gen);
	static int init = 0;
	if (init == 0) { srand((unsigned)time(NULL)), rand(), ++init; }
	return (int)((rand() / (RAND_MAX + 1.0)) * (q - p + 1.0) + p);
}
// game_set
vector<string> template_name = { "a1", "a2", "a3", "a4", "a5", "a6", "a7", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9" };
vector<string> template_str;
vector<int> deck;
void gameSet(bool EN);
// win
vector<vector<string> > pairOfWin(6);
bool winOrNot(vector <string> db, int need_pair);
vector<string> get_eyes(int a1, int a2, vector <string> s);
bool find_pair(vector <string> tmp, int left_pair);
void show_win(vector<vector<string> >tmp);
// listen
bool listenToWin(vector <string> db, int need_pair);
vector<string> listenWTF;
void show_listen(vector<string>tmp);
void show_all_cards(vector<string> db); 

void gameSet(bool EN = false) {
	for (int i = 0; i < 128; ++i)
		deck.push_back(i);
	vector<string> WordsEN = {
		"East",
		"South",
		"West",
		"North",
		"Mid",
		"Green",
		"White"
	};
	vector<string> WordsCH = {
		"東",
		"南",
		"西",
		"北",
		"中",
		"發",
		"白"
	};
	string CharactersEN = "Characters_";
	string BamboosEN = "Bamboos_";
	string CirclesEN = "Circles_";
	string CharactersCH = "萬";
	string BamboosCH = "條";
	string CirclesCH = "筒";
	if (EN)
		for (auto x : WordsEN)
			template_str.push_back(x);
	else
		for (auto x : WordsCH)
			template_str.push_back(x);
	for (int i = 0; i < 3; ++i) {
		for (int j = 1; j < 10; ++j) {
			if (i == 0)
				if (EN)
					template_str.push_back(CharactersEN + to_string(j));
				else
					template_str.push_back(CharactersCH + to_string(j));
			else if (i == 1)
				if (EN)
					template_str.push_back(BamboosEN + to_string(j));
				else
					template_str.push_back(BamboosCH + to_string(j));
			else if (i == 2)
				if (EN)
					template_str.push_back(CirclesEN + to_string(j));
				else
					template_str.push_back(CirclesCH + to_string(j));
		}
	}
}

bool winOrNot(vector <string> db, int need_pair = 6) {
	sort(db.begin(), db.end());
	for (int i = 0; i < db.size(); ++i) {
		for (int j = 0; j < db.size(); ++j) {
			if (i >= j)continue;
			if (db[i] != db[j]) continue;
			pairOfWin[0] = {db[i],db[j]};
			if (find_pair(get_eyes(i, j, db), need_pair - 1)) 
				return true;
		}
	}
	return false;
}
vector<string> get_eyes(int a1, int a2, vector <string> s) {
	vector <string> ans;
	for (int i = 0; i < s.size(); ++i)
		if (i != a1 && i != a2)
			ans.push_back(s[i]);
	return ans;
}
bool is_pair(vector <string> &the4) {
	if (the4.size() < 3)
		return false;
	char the4_type = the4[0][0];
	bool all_same = true;
	bool all_ship = true;
	for (int i = 0; i < 3; ++i) 
		if (the4_type != the4[i][0])
			return false;
	for (int i = 0; i < 3; ++i) 
		if (the4[i] != the4[0])
			all_same = false;
	int j = 1;
	for (int i = 0; i < 2; ++i, ++j)
		if (the4[i][1] + 1 != the4[j][1])
			all_ship = false;
	if ((all_ship && the4_type != 'a')|| all_same)
		return true;
	return false;
}
bool find_pair(vector <string> tmp, int left_pair) {
	if (left_pair == 0) {
		if(tmp.size() == 0)
			return true;
		else
			return false;
	}
	vector <string> the4;
	for (int i = 0; i < 4 && i < tmp.size(); ++i)
		the4.push_back(tmp[i]);
	if (the4.size() == 0)
		return false;
	string tmp_str = the4[0];
	char tmp_type = the4[0][0];
	bool four_same = true;
	for (int i = 0; i < the4.size(); ++i) {
		if (the4[i][0] != tmp_type && i < 3)
			return false;
		if (the4[i] != tmp_str) 
			four_same = false;
	}
	if (four_same && tmp.size()==4 && tmp.size() > left_pair * 3) {
		vector<string> tmp_4;
		for (int i = 4; i < tmp.size(); ++i) {
			tmp_4.push_back(tmp[i]);
		}
		pairOfWin[6-left_pair] = the4;
		if (find_pair(tmp_4, left_pair - 1))
			return true;
	}
	if (is_pair(the4)) {
		vector<string> tmp_3;
		for (int i = 3; i < tmp.size(); ++i) {
			tmp_3.push_back(tmp[i]);
		}
		pairOfWin[6 - left_pair] = {the4[0],the4[1],the4[2]};
		if (find_pair(tmp_3, left_pair - 1))
			return true;
	}
	return false;
}
void show_win(vector<vector<string> >tmp) {
	int index = -1;
	cout << "--------------------\nYOU WIN : true\n--------------------" << endl;
	for (auto x : tmp) {
		if (x.size() != 0) {
			index++;
			if (index == 0) {
				cout << "Eyes  : ";
			}
			else {
				cout << "Pair" << index << " : ";
			}
			for (auto y : x) {
				for (int i = 0; i < template_name.size(); ++i)
					if (y == template_name[i]) {
						cout << template_str[i] << " ";
						break;
					}
			}
			cout << endl;
		}
	}
}

bool listenToWin(vector <string> db, int need_pair = 6) {
	db.push_back("");
	listenWTF = {};
	int index = db.size() - 1;
	for (auto x : template_name) {
		int count = 1;
		bool jump = false;
		for (auto y : db) {
			if (y == x)
				if (count < 4)
					count++;
				else
					jump = true;
		}
		if (jump) continue;
		db[index] = x;
		if (winOrNot(db, need_pair))
			listenWTF.push_back(x);
	}
	if (listenWTF.size() != 0) {
		return true;
	}
	return false;
}
void show_listen(vector<string>tmp) {
	if (tmp.size() != 0) {
		cout << "You now listen... : ";
		for (auto x : tmp)
			for (int i = 0; i < template_name.size(); ++i)
				if (x == template_name[i]) {
					cout << template_str[i] << " ";
					break;
				}
		cout << endl;
	}
	else {
		cout << "No listening..." << endl;
	}
}
void show_all_cards(vector<string> db) {
	if (!is_sorted(db.begin(), db.end()))
		sort(db.begin(), db.end());
	if (db.size() != 0) {
		cout << "You have cards (" << db.size() << "): ";
		int index = 0;
		for (auto x : db)
			for (int i = 0; i < template_name.size(); ++i)
				if (x == template_name[i]) {
					index++;
					if (index != db.size())
						cout << template_str[i] << ", ";
					else
						cout << template_str[i];
					break;
				}
		cout << endl;
	}
}
void give_cards(vector<string>& db, int num, vector<int> &deck ) {
	if (db.size() >= num)
		return;
	bool deck_opt = true;
	if (deck.size() == 0)deck_opt = false;
	string new_cards = "";
	int fordeckNum = -1;
	if (!deck_opt) {
		int wtf = randomInt(0, 33);
		new_cards = template_name[wtf];
	}
	else {
		int wtf= randomInt(0, deck.size()-1);
		fordeckNum = deck[wtf];
		new_cards = template_name[deck[wtf]/4];
	}
	
	int count = 0;
	for (auto x : db) {
		if (new_cards == x)
			count++;
	}
	if (count != 4) {
		db.push_back(new_cards);
		int index = -1;
		for (int i = 0; i < deck.size(); ++i) {
			if(deck_opt)
				if (deck[i] == fordeckNum) {
					index = i;
				}
		}
		if (index != -1) {
			auto it = deck.begin();
			deck.erase(it + index);
		}
	}
	return give_cards(db, num,deck);
}
void drop_cards(vector<string>& db, string card_which) {
	for (int i = 0; i < db.size(); ++i) {
		if(db[i] == card_which){
			auto it = db.begin();
			db.erase(it+i);
			return;
		}
	}
}
int main() {
	// setGame
	gameSet(false);
	// input
	vector<string> db;
	while (true) {
		system("cls");
		give_cards(db, 17, deck);
		cout << "卡池剩下..." << deck.size() << endl;
		show_all_cards(db);
		// calculate
		bool win = winOrNot(db, 6);
		if (win) {
			show_win(pairOfWin);
			break;
		}
		else {
			set<string> s;
			for (auto x : db) {
				s.insert(x);
			}
			for (auto x : s) {
				vector<string> tmp = {};
				bool once = true;
				for (auto y : db) {
					if (x == y && once) {
						once = false;
						continue;
					}
					tmp.push_back(y);
				}
				if (listenToWin(tmp, 6)) {
					cout << "打掉 \"" << x << "\" 的話 -> ";
					show_listen(listenWTF);
				}
			}
			string com = "";
			cout << "\n\nDrop Cards = ";
			cin >> com;
			drop_cards(db, com);
		}
	}
	////example
	//// setGame
	//gameSet(false);
	//// input
	//vector<string> db;
	//db.push_back("b1");
	//db.push_back("b1");
	//db.push_back("b1");
	//db.push_back("b1");
	//db.push_back("b2");
	//db.push_back("b3");
	//db.push_back("b4");
	//db.push_back("b5");
	//db.push_back("b6");
	//db.push_back("b7");
	//db.push_back("b8");
	//db.push_back("b9");
	//db.push_back("b9");
	//db.push_back("b9");
	//db.push_back("a1");
	//db.push_back("a1");
	//db.push_back("a1");
	////give_cards(db, 16, deck);
	//drop_cards(db, "d1");
	//show_all_cards(db);
	//// calculate
	//bool win = winOrNot(db,6);
	//if (win)show_win(pairOfWin);
	//else {
	//	listenToWin(db, 6);
	//	show_listen(listenWTF);
	//}
	return 0;
}