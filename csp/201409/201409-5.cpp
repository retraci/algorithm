// 拼图 - 201409-5
/*
问题描述
　　给出一个n×m的方格图，现在要用如下L型的积木拼到这个图中，使得方格图正好被拼满，请问总共有多少种拼法。其中，方格图的每一个方格正好能放积木中的一块。积木可以任意旋转。

输入格式
　　输入的第一行包含两个整数n, m，表示方格图的大小。
输出格式
　　输出一行，表示可以放的方案数，由于方案数可能很多，所以请输出方案数除以1,000,000,007的余数。
样例输入
6 2
样例输出
4
样例说明
　　四种拼法如下图所示：

评测用例规模与约定
　　在评测时将使用10个评测用例对你的程序进行评测。
　　评测用例1和2满足：1<=n<=30，m=2。
　　评测用例3和4满足：1<=n, m<=6。
　　评测用例5满足：1<=n<=100，1<=m<=6。
　　评测用例6和7满足：1<=n<=1000，1<=m<=6。
　　评测用例8、9和10满足：1<=n<=10^15，1<=m<=7。
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define ll long long

using namespace std;

const ll MOD = 1000000007;
const int maxn = 1010;
const int maxm = 6;

int n, m;
ll dp[maxn][1 << maxm];

void dfs(int i, int j, int crt, int nex) {
//	printf("%d %d\n", crt, nex);
	if(j == m) {
		dp[i+1][nex] += dp[i][crt];
		dp[i+1][nex] %= MOD;
		return;
	}
	
	if((1 << j) & crt) {
		dfs(i, j+1, crt, nex);
	}
	
	/*
		1 1
		0 1
	*/
	if( ((1 << j) & crt) == 0 && (j+1 < m) && (1 << (j+1) & crt) == 0 && ((1 << (j+1)) & nex) == 0 ) {
		dfs( i, j+2, crt, nex | (1 << (j+1)) );
	}
	
	/*
		1 1
		1 0
	*/
	if( ((1 << j) & crt) == 0 && (j+1 < m) && ((1 << (j+1)) & crt) == 0 && ((1 << j) & nex) == 0 ) {
		dfs( i, j+2, crt, nex | (1 << j) );
	}
	
	/*
		1 0
		1 1
	*/
	if( ((1 << j) & crt) == 0 && (j+1 < m) && ((1 << (j+1)) & nex) == 0 && ((1 << j) & nex) == 0 ) {
		dfs( i, j+1, crt, nex | (1 << j) | (1 << (j+1)) );
	}
	
	/*
		0 1
		1 1
	*/
	if( ((1 << j) & crt) == 0 && (j-1 >= 0) && ((1 << (j-1)) & nex) == 0 && ((1 << j) & nex) == 0 ) {
		dfs( i, j+1, crt, nex | (1 << j) | (1 << (j-1)) );
	}
}

void solve() {
	dp[1][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int S = 0; S < (1 << m); S++) {
			dfs(i, 0, S, 0);
		}
	}
//	for(int i = 1; i <= n; i++) {
//		for(int S = 0; S < (1 << m); S++) {
//			printf("%d ",dp[i][S]);
//		}
//		printf("\n");
//	}
	
	cout << dp[n+1][0] << endl;
}

int main() {
	cin >> n >> m;
	solve();

	return 0;
}
