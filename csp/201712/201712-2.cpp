// 201712-2 游戏
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int n, k;

int main() {
	cin >> n >> k;
	vector<int> chs(n, 0);
	
	int cnt = n;
	int now = 0;
	int num = 1;
	while(cnt > 1) {
		while(chs[now]) now = (now+1)%n;
		if(num%k==0 || num%10==k) {
			//cout << now << endl;
			chs[now] = 1;
			cnt--;
		}
		
		now = (now+1)%n;
		num++;
	}
	
	for(int i = 0; i < n; i++) {
		if(chs[i] == 0) cout << i+1 << endl; 
	}
	
	return 0;
}
