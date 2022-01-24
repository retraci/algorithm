// 蓝桥杯11B 解码 
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	string str;
	cin >> str;
	
	int n = str.length();
	for(int i = 0; i < n; i++) {
		if(str[i] >= 'a' && str[i] <= 'z') {
			cout << str[i];
		} else if(str[i] >= 'A' && str[i] <= 'Z') {
			cout << str[i];
		} else {
			int cnt = str[i] - '1';
			while(cnt--) {
				cout << str[i-1];
			}
		}
	}
	cout << endl;
	
	return 0;
} 
