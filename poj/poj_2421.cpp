// POJ 2421 Constructing Roads
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 110;

struct Node {
	int from,to,w;
} edge[maxn*maxn];

int n,m,ans;
int pa[maxn];

bool cmp(const Node &a,const Node &b) {
	return a.w < b.w;
}

void init() {
	m = 0;
	ans = 0;
	for(int i=1;i<=n;i++) 
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
	int cnt = 0;
	sort(edge,edge+m,cmp);
	for(int i=0;i<m;i++) {
		if(join(edge[i].from,edge[i].to)) {
			ans += edge[i].w;
			cnt++;
		}
		if(cnt == n-1)
			break;
	}
}

int main() {
	int q,w;
	cin >> n;
	init();
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cin >> w;
			if(i == j)
				continue;
			edge[m].from = i;
			edge[m].to = j;
			edge[m].w = w;
			m++;
		}
	}
	
	cin >> q;
	int a,b;
	int cnt = 0;
	while(q--) {
		cin >> a >> b;
		join(a,b);
		cnt++;
	}
	
	Kruskal();
	cout << ans;
	
	return 0;
}

