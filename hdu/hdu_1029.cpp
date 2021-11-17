// HDU 1029 Ignatius and the Princess IV
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 1e6+10;

int n;
int dp[maxn];

int main() {
	while(cin >> n) {
		int k,flag = 0;
		memset(dp,0,sizeof(dp));
		for(int i=0; i<n; i++) {
			cin >> k;
			dp[k]++;
			if(!flag && dp[k]>=(n+1)/2) {
				cout << k << endl;
				flag = 1;
			}
		}
	}

	return 0;
}
