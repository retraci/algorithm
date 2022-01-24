// 蓝桥杯8B k倍区间
/*
	思路：
	前缀和
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 100010;

int n, k;
ll nums[maxn];
int cnt[maxn];

int main() {
	cin >> n >> k;

	for(int i = 1; i <= n; i++) {
		scanf("%I64d", &nums[i]);
		nums[i] = (nums[i] + nums[i-1]) % k;
	}
	
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += cnt[nums[i]];
		cnt[nums[i]]++;
	}
	ans += cnt[0];
	cout << ans << endl;

	return 0;
}
