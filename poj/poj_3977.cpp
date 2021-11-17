// POJ 3977 Subset
/*
	思路：
	折半枚举
	
	node:
	pair 先对比 first 再对比 second 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;

const ll INF = 0x3f3f3f3f;

int n;
ll nums[50];
map<ll, ll> mp;

void solve() {
	mp.clear();
	int m, lim;
	P ans = P(fabs(nums[0]), 1);

	// 保存前一半
	m = n/2;
	lim = 1 << m;
	for(int s = 1; s < lim; s++) {
		ll sum = 0, cnt = 0;
		for(int i = 0; i < m; i++) {
			if((1<<i) & s) {
				sum += nums[i];
				cnt++;
			}
		}
		ans = min(ans, P(fabs(sum), cnt));
		if(mp[sum]) mp[sum] = min(mp[sum], cnt);
		else mp[sum] = cnt;
	}

	// 后一半枚举
	m = n - n/2;
	lim = 1 << m;
	for(int s = 1; s < lim; s++) {
		ll sum = 0, cnt = 0;
		for(int i = 0; i < m; i++) {
			if((1<<i) & s) {
				sum += nums[n/2 + i];
				cnt++;
			}
		}

		ans = min(ans, P(fabs(sum), cnt));

		map<ll, ll>::iterator it = mp.lower_bound(-sum);
		if(it != mp.end()) {
			ans = min(ans, P(fabs(it->first+sum), cnt+it->second));
		}
		if(it != mp.begin()) {
			it--;
			ans = min(ans, P(fabs(it->first+sum), cnt+it->second));
		}
	}
	cout << ans.first << " " << ans.second << endl;
}

int main() {
	while(cin >> n && n) {
		for(int i = 0; i < n; i++) {
			scanf("%I64d", &nums[i]);
		}

		solve();
	}

	return 0;
}
