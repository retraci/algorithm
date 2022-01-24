// 蓝桥杯 九宫幻方
/*

*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n;
int vis[10];
int nums[3][3];
vector<int> ze;
int cnt;
int ans[3][3];

bool judge() {
	int temp;
	temp = nums[0][0]+nums[0][1]+nums[0][2];
	if(temp != 15) return false;
	temp = nums[1][0]+nums[1][1]+nums[1][2];
	if(temp != 15) return false;
	temp = nums[2][0]+nums[2][1]+nums[2][2];
	if(temp != 15) return false;

	temp = nums[0][0]+nums[1][0]+nums[2][0];
	if(temp != 15) return false;
	temp = nums[0][1]+nums[1][1]+nums[2][1];
	if(temp != 15) return false;
	temp = nums[0][2]+nums[1][2]+nums[2][2];
	if(temp != 15) return false;

	temp = nums[0][0]+nums[1][1]+nums[2][2];
	if(temp != 15) return false;
	temp = nums[0][2]+nums[1][1]+nums[2][0];
	if(temp != 15) return false;

	return true;
}

void dfs(int x) {
	if(cnt >= 2) return;
	if(x == n) {
		if(judge()) {
			cnt++;
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 3; j++) {
					ans[i][j] = nums[i][j];
				}
			}
		}
		return;
	}

	for(int i = 1; i <= 9; i++) {
		if(vis[i]) continue;
		vis[i] = 1;
		int nx = ze[x] / 3;
		int ny = ze[x] % 3;
		nums[nx][ny] = i;
		dfs(x+1);
		nums[nx][ny] = 0;
		vis[i] = 0;
	}
}

void solve() {
	n = ze.size();
	dfs(0);

	if(cnt == 1) {
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(j != 2)
					cout << ans[i][j] << " ";
				else
					cout << ans[i][j] << endl;
			}
		}
	} else {
		cout << "Too Many" << endl;
	}
}

int main() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			cin >> nums[i][j];
			vis[nums[i][j]] = 1;
			if(nums[i][j] == 0) ze.push_back(i*3+j);
		}
	}
	solve();

	return 0;
}
