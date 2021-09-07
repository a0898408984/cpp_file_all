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
bool check2(vector<int> tar, vector<char> c, int num) {
	vector<int> s;
	int sum = 0;
	for (int i = 0; i < num; ++i) {
		if (c[i] == 'o') {
			++sum;
		}
		else if (c[i] != 'o' && sum != 0) {
			s.push_back(sum);
			sum = 0;
		}
		if (sum != 0 && i == num - 1)
			s.push_back(sum);
	}
	return (s == tar);
}
bool check(int n ,int m, char * &c, vector<vector<int> > &r1, vector<vector<int> > &r2) {
	vector<char> d(5);
	// row
	for (int i = 0; i < n; ++i) {
		d = { '_','_','_','_','_' };
		for (int j = 0; j < m; ++j) {
			d[j] = c[i * m + j];
		}
		if (!check2(r1[i], d, n))
			return false;
	}
	// col
	for (int i = 0; i < m; ++i) {
		d = { '_','_','_','_','_' };
		for (int j = 0; j < n; ++j) {
			d[j] = c[j * m + i];
		}
		if (!check2(r2[i], d, m))
			return false;
	}
	return true;
}
void test() {
	char* c = new char[16];
	for (int i = 0; i < 10; i++) {
		c[i] = 'o';
	}
	for (int i = 10; i < 16; i++) {
		c[i] = 'x';
	}
	int sum = 0;
	do {
		++sum;
	} while (next_permutation(c, c + 16));
	cout << sum;
}
int main() {
	//4 4 2 1 1 2 1 1 2 1 1 1 4 2 1 2 2 1 1 2 1 2 2 1 1 
	//5 5 1 4 1 2 1 3 1 2 1 4 2 1 1 2 3 1 3 1 1 1 2 1 3 2 1 1 
	int n = 0, m = 0, sum = 0;
	bool limit = 1;
	cin >> n >> m;
	char* c = new char[n*m];
	vector<vector<int> > r1(n),r2(m);
	for (int i = 0; i < n; ++i) {
		int tmp = 0,tmp2= 0;
		cin >> tmp;
		for (int j = 0; j < tmp; ++j) {
			cin >> tmp2;
			r1[i].push_back(tmp2);
		}	
	}
	for (int i = 0; i < m; ++i) {
		int tmp = 0, tmp2 = 0;
		cin >> tmp;
		for (int j = 0; j < tmp; ++j) {
			cin >> tmp2;
			r2[i].push_back(tmp2);
		}
	}
	clock_t t1;
	t1 = clock();
	for (auto x : r1) {
		for (auto y : x) {
			sum += y;
		}
	}
	for (int i = 0; i < n * m; ++i) {
		if (i < sum) {
			c[i] = 'o';
		}
		else {
			c[i] = 'x';
		}
	}
	int count = 0;
	do {
		if (check(n, m, c, r1, r2)) {
			for (int i = 0; i < m * n; ++i){
				if (i % m == 0 && i != 0)cout << endl;
				cout << (c[i]=='o'?'o':'_');
			}
			++count;
			break;
		}
	} while (next_permutation(c, c + m*n));
	delete[] c;
	printf("\n\nTotal run in  %f s.\n", double(clock() - t1) / 1000);
	system("pause");
	return 0;
}