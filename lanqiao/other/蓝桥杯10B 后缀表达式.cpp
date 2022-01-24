// 蓝桥杯10B 后缀表达式
/*
	思路：
	分类
	
	node：
	前缀，后缀表达式，顺序就可以代表运算顺序 
*/

#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> numsN;
vector<int> numsP;

void solve() {
	int ans = 0;
	if(m <= numsN.size()) {
		for(int i = 0; i < numsP.size(); i++) {
			ans += numsP[i];
		}
		for(int i = 0; i < numsN.size(); i++) {
			ans -= numsN[i];
		}
	} else {
		int del = m - numsN.size();
		sort(numsP.begin(), numsP.end());
		
		for(int i = 0; i < numsP.size(); i++) {
			if(i < del) {
				ans -= numsP[i];
			} else {
				ans += numsP[i];	
			}

		}
		for(int i = 0; i < numsN.size(); i++) {
			ans -= numsN[i];
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> m;
	
	int temp;
	for(int i = 0; i < n+m+1; i++) {
		scanf("%d", &temp);
		if(temp < 0) numsN.push_back(temp);
		else numsP.push_back(temp);
	}
	
	solve();
	
	return 0;
}
