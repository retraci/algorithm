// HDU 1087 Super Jumping! Jumping! Jumping!
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1010;

int n;
int dp[maxn];			// 1-i 最大值，且必须有 i 
int a[maxn];

int main() {
	while(~scanf("%d",&n) && n) {
		memset(dp,0,sizeof dp);
		for(int i=1;i<=n;i++) 
			scanf("%d",&a[i]);
		
		for(int i=1;i<=n;i++) {
			dp[i] = a[i];
			for(int j=1;j<=i-1;j++) {
				if(a[i]>a[j])
					dp[i] = max(dp[i],dp[j]+a[i]);
			}
		}
		
		int ans = -1;
		for(int i=1;i<=n;i++) {
			ans = max(ans,dp[i]);
		}
		cout << ans << endl;
	}
	
	return 0;
}
