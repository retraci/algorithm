// POJ 1287 Networking
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 55;
struct Node {
	int from,to,w;
} Edge[maxn*maxn];

int n,m,ans;
int pa[maxn];

bool cmp(const Node &a,const Node &b) {
	return a.w < b.w;
}

void init() {
	ans = 0;
	for(int i=0; i<=n; i++)
		pa[i] = i;
}

int find(int x) {
	if(x == pa[x])
		return x;
	int temp = pa[x];
	pa[x] = find(temp);
	return pa[x];
}

bool join(int x,int y) {
	int rx,ry;
	rx = find(x);
	ry = find(y);
	if(rx == ry)
		return false;
	else
		pa[rx] = ry;
	return true;
}

void Kruskal() {
	sort(Edge,Edge+m,cmp);
	int cnt = 0;
	for(int i=0; i<m; i++) {
		if(join(Edge[i].from,Edge[i].to)) {
			cnt++;
			ans += Edge[i].w;
		}
		if(cnt == n-1)
			break;
	}
}

int main() {
	int x,y,w;
	while(cin >> n >> m) {
		if(n == 0) break;
		init();
		for(int i=0; i<m; i++) {
			cin >> x >> y >> w;
			Edge[i].from = x;
			Edge[i].to = y;
			Edge[i].w = w;
		}

		Kruskal();
		cout << ans << endl;
	}

	return 0;
}
