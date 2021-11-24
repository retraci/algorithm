// HDU 2084 数塔
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxn = 110;

int n;
int dp[maxn][maxn];			// i行j列的最大值 

int main() {
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=i;j++) 
				scanf("%d",&dp[i][j]);
		
		for(int i=n-1;i>=1;i--) {
			for(int j=1;j<=i;j++) {
				dp[i][j] += max(dp[i+1][j],dp[i+1][j+1]);
			}
		}
		cout << dp[1][1] << endl;
	}
	
	return 0;
}
