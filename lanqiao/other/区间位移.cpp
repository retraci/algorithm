// 蓝桥杯 区间位移 
/*
	思路：
	二分答案 
	
	node:
	由于小数只能是 0.5 所以直接乘二 方便二分答案 
	
	右边界小优先（搭桥作用），左边界小优先
	原因所有线段都可以用，
	如果限定线段数目，则左边界小优先，尽量向右 
*/

#include <bits/stdc++.h>

using namespace std;

struct line {
	int l, r;
	line(int l_, int r_) {
		l = l_; r = r_;
	}
};

const int maxn = 10010;

int n;
vector<line> arr;
int ll[maxn], rr[maxn];
bool vis[maxn];

// 右边界小优先，左边界小优先 
bool cmp(line lin1, line lin2) {
	return lin1.r == lin2.r ? lin1.l < lin2.l : lin1.r < lin2.r;
}

bool check(int s) {
	memset(vis, false, sizeof(vis));
	int rcd = 0;
	
	while(rcd < 20000) {
		// 寻找开始遍历的起点，即 pos >= rcd-s 的最小值 
		int pos = lower_bound(rr, rr+n, rcd-s) - rr;
		//    前提条件     用过       左边界够不到 
		while(pos < n && (vis[pos] || ll[pos]>rcd+s)) pos++;
		if(pos == n) return false;
		vis[pos] = 1;
		// 如果左边界+可移动长度 在右边 则从 rcd 加长度 
		if(ll[pos] + s >= rcd) rcd += rr[pos] - ll[pos];
		// 如果左边界+可移动长度 在左边 则从左边 加长度 
		else rcd = ll[pos] + s + rr[pos] - ll[pos];
	}
	
	return true;
}

void solve() {
	sort(arr.begin(), arr.end(), cmp);
	for(int i = 0; i < n; i++) {
		ll[i] = arr[i].l; rr[i] = arr[i].r;
	}
	
	int ans = 0;
	int lf = 0, rt = 0x3f3f3f3f;
	while(lf <= rt) {
		int mid = (lf+rt) >> 1;
		if(check(mid)) {
			ans = mid;
			rt = mid-1;
		} else {
			lf = mid+1;
		}
	}
	
	cout << ans/2.0 << endl;
}

int main() {
	cin >> n;
	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		arr.push_back(line(a*2, b*2));
	}
	solve();
	
	return 0;
}
