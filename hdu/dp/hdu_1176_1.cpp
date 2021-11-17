// HDU 1176 免费馅饼 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxx = 13;
const int maxt = 100010;

int n;
int dp[maxt][maxx];

int main() {
	while(~scanf("%d",&n) && n) {
		memset(dp,0,sizeof dp);
		int x,t;
		int tt=-1;
		for(int i=1;i<=n;i++) {
			scanf("%d%d",&x,&t);
			dp[t][x+1]++;
			tt = max(tt,t);
		}
		// 一共要做 tt 次决策 , t=1时也需要做决策 
		// for(int i=1;i<=tt;i++)
		for(int i=tt-1;i>=0;i--) {
			for(int j=1;j<=11;j++) {
				dp[i][j] += max(dp[i+1][j-1],max(dp[i+1][j],dp[i+1][j+1]));
			}
		}
		cout << dp[0][6] << endl;
	}
	
	
	return 0;
}
