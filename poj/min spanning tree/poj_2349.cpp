// POJ 2349 Arctic Network
// Kruskal + 贪心
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 510;

struct Node {
	int x,y;
} node[maxn];

struct Edge {
	int from,to;
	double w;
} edge[maxn*maxn];

int S;
int n,m,pa[maxn];
double d[maxn];

double get_dist(int a,int b) {
	double temp = (node[a].x-node[b].x)*(node[a].x-node[b].x)+(node[a].y-node[b].y)*(node[a].y-node[b].y);
	return sqrt(temp);
}

bool cmp(Edge a,Edge b) {
	return a.w < b.w;
}

void init() {
	for(int i=0; i<n; i++) {
		pa[i] = i;
	}
}

int find(int x) {
	if(x == pa[x]) return x;
	int temp = pa[x];
	pa[x] = find(temp);
	return pa[x];
}

bool join(int x,int y) {
	int rx = find(x);
	int ry = find(y);
	if(rx == ry) return false;
	else {
		pa[rx] = ry;
		return true;
	}
}

void Kruskal() {
	sort(edge,edge+m,cmp);
	int cnt = 0;
	for(int i=0; i<m; i++) {
		if(join(edge[i].from,edge[i].to)) {
			d[cnt++] = edge[i].w;
		}
		if(cnt >= n-1)
			break;
	}
}

int main() {
	int N;
	cin >> N;
	while(N--) {
		cin >> S >> n;
		init();
		m = 0;
		for(int i=0; i<n; i++) {
			cin >> node[i].x >> node[i].y;
		}
		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				double dis = get_dist(i,j);
				edge[m].from = i;
				edge[m].to = j;
				edge[m].w = dis;
				m++;
			}
		}
		Kruskal();
		printf("%.2lf\n",d[n-S-1]);
	}

	return 0;
}
