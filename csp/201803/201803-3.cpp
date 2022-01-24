// 201803-3
/*
	思路：
	字符串处理 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

int n, m;
string str1[maxn];
string str2[maxn];
string str;

bool check(string& s1, string& s2) {
	int len1 = s1.size();
	int len2 = s2.size();
	int p1 = 0, p2 = 0;

	while(p1 < len1 && p2 < len2) {
		// 字符匹配
		if(s1[p1] == s2[p2]) {
			p1++, p2++;
			continue;
		}

		// 匹配格式
		if(s2[p2] && s2[p2] != '<') return false;
		if(s2[p2] && s2[p2] == '<') {
			p2++;

			if(s2[p2] && s2[p2] == 'i') {
				int flag = 0;
				while(s1[p1] && isdigit(s1[p1])) {
					if(s1[p1] != '0') flag = 1;
					p1++;
				}
				if(!flag) return false;
				p2 += 4;
			} else if(s2[p2] && s2[p2] == 's') {
				while(s1[p1] && s1[p1] != '/') p1++;
				p2 += 4;
			} else if(s2[p2] && s2[p2] == 'p') {
				return true;
				p2 += 5;
			}
		}

	}

	return p1==len1 && p2==len2;
}

void print(string& s1, string& s2) {
	int len1 = s1.size();
	int len2 = s2.size();
	int p1 = 0, p2 = 0;

	while(p1 < len1 && p2 < len2) {
		// 字符匹配
		if(s1[p1] == s2[p2]) {
			p1++, p2++;
			continue;
		}

		// 匹配格式
		if(s2[p2] && s2[p2] == '<') {
			p2++;

			if(s2[p2] && s2[p2] == 'i') {
				int flag = 0;
				cout << " ";
				while(s1[p1] && isdigit(s1[p1])) {
					if(flag == 0 && s1[p1] == '0') {
						p1++;
						continue;
					}
					flag = 1;
					cout << s1[p1];
					p1++;
				}
				p2 += 4;
			} else if(s2[p2] && s2[p2] == 's') {
				cout << " ";
				while(s1[p1] && s1[p1] != '/') {
					cout << s1[p1];
					p1++;
				}
				p2 += 4;
			} else if(s2[p2] && s2[p2] == 'p') {
				cout << " ";
				while(s1[p1]) {
					cout << s1[p1];
					p1++;
				}
			}
		}
	}
}

void solve() {
	int flag = 0;
	for(int i = 0; i < n; i++) {
		if(check(str, str1[i])) {
			flag = 1;
			cout << str2[i];
			print(str, str1[i]);
			cout << endl;
			break;
		}
	}
	if(!flag) cout << 404 << endl;
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		cin >> str1[i] >> str2[i];
	}
	for(int i = 0; i < m; i++) {
		cin >> str;
		solve();
	}

	return 0;
}
