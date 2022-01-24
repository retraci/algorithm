// 蓝桥杯2018B 搭积木
/*
	思路：
	dp + 二维前缀和
*/

#include <bits/stdc++.h>

#define LL long long

using namespace std;

const int MOD = 1e9 + 7;
const int maxn = 110;

int n, m;
LL dp[maxn][maxn][maxn];
int c[maxn][maxn];
LL s[maxn][maxn];

void get_prefix_sum(int k) {
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= m; j++) {
			s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + dp[k][i][j];
		}
	} 
}

LL get_sum(int x1, int x2, int y1, int y2) {
	return (s[x2][y2] - s[x1-1][y2] - s[x2][y1-1] + s[x1-1][y1-1] + MOD ) % MOD;
}
 
int main() {
	cin >> n >> m;

	for(int k = n; k >= 1; k--) {
		string temp;
		cin >> temp;
		c[k][0] = 0;
		for(int i = 0; i < temp.size(); i++) {
			c[k][i+1] = c[k][i] + (temp[i] == 'X');
		}
	}
	
	LL ans = 1;
	dp[0][1][m] = 1;
	get_prefix_sum(0);
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= m; i++) {
			for(int j = i; j <= m; j++) {
				if(c[k][j]-c[k][i-1] != 0) continue;
				
				// 相当于 求 x = [1, i] 
				//  		 y = [j, m] 的面积 
//				for(int x = 1; x <= i; x++) {
//					for(int y = j; y <= m; y++) {
//						dp[k][i][j] = (dp[k][i][j] + dp[k-1][x][y]) % MOD;
//					}
//				}
				
				dp[k][i][j] = (dp[k][i][j] + get_sum(1, i, j, m)) % MOD;			
				ans = (ans + dp[k][i][j]) % MOD;
			}
		}
		get_prefix_sum(k);
	}
	
	cout << ans << endl;

	return 0;
}
