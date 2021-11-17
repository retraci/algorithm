// POJ 2566 Bound Found
/*
	思路：
	前缀和，尺取法
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;

const ll maxn = 100010;

struct Node {
	ll val, pos;
};

ll n, k, tar;
Node nums[maxn];

bool cmp(Node n1, Node n2) {
	return n1.val < n2.val;
}

void solve() {
	ll del = 0x3f3f3f3f;
	ll l, r, tot;

	// 动态尺取法
	int i = 0, j = 1;
	while(j <= n) {
		if(!del) break;
		ll temp = fabs(nums[i].val-nums[j].val);
		if(fabs(tar-temp) < del) {
			del = fabs(tar-temp);
			tot = temp;
			l = nums[i].pos; r = nums[j].pos;
		}
		if(temp < tar) j++;
		if(temp > tar) i++;
		if(i == j) j++;
	}

	if(l > r) swap(l, r);
	printf("%I64d %I64d %I64d\n", tot, l+1, r);
}

int main() {
	while(cin >> n >> k && n && k) {
		nums[0].val = 0;
		nums[0].pos = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%I64d", &nums[i].val);
			nums[i].val += nums[i-1].val;
			nums[i].pos = i;
		}
		sort(nums, nums+1+n, cmp);
		for(int i = 0; i < k; i++) {
			scanf("%I64d", &tar);
			solve();
		}
	}

	return 0;
}
