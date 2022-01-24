// 蓝桥杯 图形排版
/*
	思路：
	倒着推一次，纪录 
	顺着推找最优解
	
	node: 取上界 = ( (all分子-1) / 分母 ) +1 
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1e5+10;

struct paper {
	int w, h;
	paper(int w_, int h_) {
		w = w_; h = h_;
	}
};

int m, n;
int rev[maxn];
vector<paper> ps;

void add(paper& p, int k) {
	if(p.w + ps[k].w <= m) {
		p.w += ps[k].w;
		p.h = max(p.h, ps[k].h);
	} else {
		int temp = m - p.w;
		p.h = max(p.h, (temp*ps[k].h-1)/ps[k].w + 1);
		p.w = m;
	}
}

// 获取 k 到 n 
int get_rev(paper p, int k) {
	// 填完 p 行 
	while(p.w < m && k < n) {
		add(p, k++);
	}
	// p 行 + 从 k 开始到 n 
	return p.h + rev[k];
}

void solve() { 
	// 初始化 rev 
	for(int i = n-1; i >= 0; i--) {
		rev[i] = get_rev(paper(0, 0), i);
	}
	
	int ans = 0x3f3f3f3f;
	int h = 0;
	paper p = paper(0, 0);
	// 顺着遍历，获取状态，再按照状态来获取 i+1 到 n 
	for(int i = 0; i < n; i++) {
		ans = min(ans, h+get_rev(p, i+1));
		
		add(p, i);
		if(p.w == m) {
			h += p.h;
			p.w = p.h = 0;
		}
	}
	cout << ans << endl;
}

int main() {
	cin >> m >> n;

	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		ps.push_back(paper(a, b));
	}
	solve();

	return 0;
}
