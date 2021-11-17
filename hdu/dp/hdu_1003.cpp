// HDU 1003 Max Sum
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 100010;

int n,ans;
int dp[maxn];

int main() {
	int t;
	cin >> t;
	for(int k=1; k<=t; k++) {
		int l,r,s;
		cin >> n;
		memset(dp,0,sizeof dp);
		for(int i=1; i<=n; i++)
			cin >> dp[i];

		l=1,r=1,ans=dp[1],s=1;
		for(int i=2; i<=n; i++) {
			dp[i] = dp[i-1]>0?dp[i-1]+dp[i]:dp[i];
			if(dp[i-1]<0) 
				s = i;
			if(dp[i]>ans) {
				ans = dp[i];
				r = i;
				l = s;
			}
		}

		printf("Case %d:\n",k);
		printf("%d %d %d\n",ans,l,r);
		if(k!=t) cout << endl;
	}

	return 0;
}

