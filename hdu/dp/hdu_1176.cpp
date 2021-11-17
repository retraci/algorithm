// HDU 1176 免费馅饼
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100010;

int n;
int dp[maxn][13];		// 某个时间站在某个位置的最大收获 

int main() {
	while(scanf("%d",&n) && n) {
		int t,x,maxt=-1;
		memset(dp,0,sizeof dp);
		for(int i=0;i<n;i++) {
			scanf("%d%d",&x,&t);
			dp[t][x+1]++;
			maxt = t>maxt?t:maxt;
		}
		// 倒着推是因为只有起点是固定的 
		for(int i=maxt-1;i>=0;i--) {
			for(int j=1;j<=11;j++) {
				dp[i][j] += max(dp[i+1][j],max(dp[i+1][j-1],dp[i+1][j+1]));
			}
		}
		printf("%d\n",dp[0][6]);
	}	
	
	return 0;
}
 
