// HDU 1114 Piggy-Bank
// 完全背包问题 
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

#define INF 0x3f3f3f3f

using namespace std;

const int maxn = 510;
const int maxm = 10010;

int n,m;
int v[maxn];
int w[maxn];
int dp[maxn][maxm];				// 可选的硬币为 1~i , 背包容量为 j 

int main() {
	int t,e,f;
	cin >> t;
	while(t--) {
		// INF 表示没有办法 
		memset(dp,INF,sizeof dp);
		cin >> e >> f >> n;
		m = f-e;
		for(int i=1;i<=n;i++)
			scanf("%d%d",&v[i],&w[i]);
		
		// 初始化第一列，从 0 开始递推 
		for(int i=0;i<=n;i++) 
			dp[i][0] = 0;
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {			// 顺着来递推，可以保证硬币的选择不止 1 次 
				if(j<w[i]) 
					// 背包不够放，则直接继承 
					dp[i][j] = dp[i-1][j];
				else 
					// 放第 i 个 与 不放第 i 个
					dp[i][j] = min(dp[i][j-w[i]]+v[i],dp[i-1][j]);
			}
		}
		
//		for(int i=0;i<=n;i++) {
//			cout << dp[i][0] << endl;
//		}
		
		if(dp[n][m]<INF) {
			printf("The minimum amount of money in the piggy-bank is %d.\n",dp[n][m]);
		} else {
			printf("This is impossible.\n");
		}
	}
	
	return 0;
}
