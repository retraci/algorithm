// HDU 1087 Super Jumping! Jumping! Jumping!
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1010;

int n,ans;
int a[maxn],dp[maxn];

int main() {
	while(~scanf("%d",&n) && n) {
		ans = 0;
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			dp[i] = a[i];
		}
		for(int i=2;i<=n;i++) {
			for(int j=1;j<i;j++) {
				if(a[j]<a[i]) 
					dp[i] = a[i]+dp[j]>dp[i]?a[i]+dp[j]:dp[i];
			}
		}
		for(int i=1;i<=n;i++) ans = dp[i]>ans?dp[i]:ans;
		printf("%d\n",ans);
	}	
	
	return 0;
}

