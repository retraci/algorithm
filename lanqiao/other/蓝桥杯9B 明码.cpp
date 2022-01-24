// 蓝桥杯9B 明码
/*
	思路：
	计算 
*/

#include <bits/stdc++.h>

using namespace std;

int nums[16][2];

void print(int x) {
	stack<int> sta;
	for(int i = 0; i < 8; i++) {
		sta.push(x & 1);
		x >>= 1;
	}
	while(!sta.empty()) {
		int temp = sta.top(); sta.pop();
		if(temp) cout << '1';
		else cout << " ";
	}
}

int main() {
	int temp;
	
	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 2; j++) {
			cin >> temp;
			print(temp);
		}
		cout << endl;
	}

	return 0;
}
