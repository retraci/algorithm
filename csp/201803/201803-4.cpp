// 201803-4
/*
	思路：
	博弈论 dfs
	
	node：
	check 的 0 需要注意 
*/

#include <bits/stdc++.h>

using namespace std;

/*
1
0 0 1
0 0 0
0 0 0
*/

int a[5][5];

int check() {
	for(int i = 0; i < 3; i++) {
		if(a[i][0] != 0 && a[i][0] == a[i][1] && a[i][0] == a[i][2]) return a[i][0];
		if(a[0][i] != 0 && a[0][i] == a[1][i] && a[0][i] == a[2][i]) return a[0][i];
	}

	if(a[0][0] != 0 && a[0][0] == a[1][1] && a[0][0] == a[2][2]) return a[0][0];
	if(a[0][2] != 0 && a[0][2] == a[1][1] && a[0][2] == a[2][0]) return a[0][2];

	return 0;
}

int dfs(int x) {
	int cnt = 0;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++)
			if(a[i][j] == 0) cnt++;
	}

	int num = check();
	if(num == 1) return cnt + 1;
	if(num == 2) return -(cnt + 1);
	if(cnt == 0) return 0;

	int res;
	if(x == 1) res = -100;
	else res = 100;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(a[i][j]) continue;
			a[i][j] = x;
			if(x == 1) res = max(res, dfs(2));
			if(x == 2) res = min(res, dfs(1));
			a[i][j] = 0;
		}
	}

	return res;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				scanf("%d", &a[i][j]);

		cout << dfs(1) << endl;
	}

	return 0;
}
