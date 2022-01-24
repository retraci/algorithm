// 食物链 - POJ 1182
/*
	利用向量关系，A 吃 B 转化为 A -> B，同类则 A -> A

	用并查集：同一个动物，需要 3 个属性来表示他属于 A,B 或 C
	1 吃 2 则，	1_A -> 2_B，
				1_B -> 2_C，
				1_C -> 2_A;

	同类则会 	1_A -> 2_A，....
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 5e4+10;

int n, m, ans;
int d, x, y;
int p[maxn*3];

int find(int x) {
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}


void join(int x, int y) {
	int fx, fy;
	fx = find(x), fy = find(y);
	if(fx != fy) p[fx] = fy;
}

void solve() {
	if(x < 1 || x > n || y < 1 || y > n) {
		ans++;
		return;
	}

	// x,y same
	if(d == 1) {
		int fx = find(x), fy1 = find(y+n), fy = find(y), fx1 = find(x+n);
		if(fx == fy1 || fy == fx1) ans++;
		else {
			join(x, y);
			join(x+n, y+n);
			join(x+2*n, y+2*n);
		}
	}

	// x -> y
	if(d == 2) {
		if(x == y) {
			ans++;
			return;
		}
		int fx = find(x), fy = find(y), fx1 = find(x+n);
		if(fx == fy || fy == fx1) ans++;
		else {
			join(x, y+n);
			join(x+n, y+2*n);
			join(x+2*n, y);
		}
	}

}

int main() {
	cin >> n >> m;
	ans = 0;
	for(int i=1; i<=n*3; i++) p[i] = i;

	for(int i=0; i<m; i++) {
		scanf("%d%d%d", &d, &x, &y);
		solve();
	}
	cout << ans << endl;

	return 0;
}
