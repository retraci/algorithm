// POJ 2031 Build a Space Station
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 110;
struct Node {
	double x,y,z,r;
} node[maxn];

struct Edge {
	int from,to;
	double w;
} edge[maxn*maxn];

int n,m;
double ans;
int pa[maxn];

bool cmp(const Edge &a,const Edge &b) {
	return a.w < b.w;
}

void init() {
	ans = 0;
	m = 0;
	for(int i=0; i<n; i++)
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
	sort(edge,edge+m,cmp);
	int cnt = 0;
	for(int i=0; i<m; i++) {
		if(join(edge[i].from,edge[i].to)) {
			cnt++;
			ans += edge[i].w;
		}
		if(cnt == n-1)
			break;
	}
}

double get_dis2(int i,int j) {
	Node p1 = node[i];
	Node p2 = node[j];
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z);
}

int main() {
	double dis2,r2,w;
	while(cin >> n) {
		if(n == 0)
			break;
		init();
		for(int i=0; i<n; i++) {
			cin >> node[i].x >> node[i].y >> node[i].z >> node[i].r;
		}
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(i == j)
					continue;
				dis2 = get_dis2(i,j);
				r2 = node[i].r+node[j].r;
				w = sqrt(dis2)-r2;
				if(w < 0) w = 0;
				edge[m].from = i;
				edge[m].to = j;
				edge[m].w = w;
				m++;
			}
		}
		Kruskal();
		printf("%.3f\n",ans);
	}

	return 0;
}

