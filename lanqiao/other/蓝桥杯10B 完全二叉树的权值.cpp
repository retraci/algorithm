// 蓝桥杯10B 完全二叉树的权值 
/*
	思路：
	遍历 
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

int n;
int nums[MAXN];

void solve() {
	int mx = 0, cur = 1, cnt = 1, ans;
	
	int i = 0;
	while(i < n) {
		int temp = 0;
		for(int j = 0; j < cnt; j++) {
			if(i >= n) break;
			temp += nums[i++];
		}
		if(temp > mx) {
			mx = temp;
			ans = cur;
		}
		cur++;
		cnt *= 2;
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	
	solve();
	
	return 0;
}

