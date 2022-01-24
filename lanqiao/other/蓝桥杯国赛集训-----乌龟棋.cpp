// 蓝桥杯国赛集训-----乌龟棋
/*

*/

#include <bits/stdc++.h>

using namespace std;

int n, m;
int card[5];
vector<int> nums;
int dp[45][45][45][45];

void solve() {
	dp[0][0][0][0] = nums[1];
	for (int a = 0; a <= card[1]; a++) {
		for (int b = 0; b <= card[2]; b++) {
			for (int c = 0; c <= card[3]; c++) {
				for (int d = 0; d <= card[4]; d++) {
					int step = a+2*b+3*c+4*d + 1;
					if (a-1 >= 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a-1][b][c][d] + nums[step]);
					if (b-1 >= 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b-1][c][d] + nums[step]);
					if (c-1 >= 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c-1][d] + nums[step]);
					if (d-1 >= 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d-1] + nums[step]);
				}
			}
		}
	}
	cout << dp[card[1]][card[2]][card[3]][card[4]] << endl;
}

int main() {
	cin >> n >> m;
	nums = vector<int> (n+1, 0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nums[i]);
	}
	int tmp;
	for (int i = 0; i < m; i++) {
		scanf("%d", &tmp);
		card[tmp]++;
	}
	solve();

	return 0;
}
