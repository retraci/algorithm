// POJ 2728 Desert King
/*
	思路：
	01分数规划
	最优比率生成树
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

struct Point {
	double x, y, z;
};

const double eps = 1e-5;
const int maxn = 1010;

int n;
Point vp[maxn];
int vis[maxn];
double dist[maxn];
double vh[maxn][maxn];
double vl[maxn][maxn];

double calc(int u, int v, double mid) {
	return vh[u][v] - mid * vl[u][v];
}

double prim(double mid) {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++) dist[i] = 0x3f3f3f3f;
	
	dist[0] = 0;
	double res = 0;
	for (int k = 0; k < n; k++) {
		int mine = 0;
		double minc = 0x3f3f3f3f;
		for (int i = 0; i < n; i++) {
			if (!vis[i] && minc > dist[i]) {
				mine = i;
				minc = dist[i];
			}
		}
		
		int u = mine;
		res += minc;
		vis[mine] = 1;
		for (int i = 0; i < n; i++) {			
			double dis = calc(u, i, mid);
			
			if (!vis[i] && dist[i] > dis) {
				dist[i] = dis;
			}
		}
	}
	
	return res;
}

bool check(double mid) {
	double res = prim(mid);
	return res <= 0;
}

void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			vh[i][j] = vh[j][i] = fabs(vp[i].z-vp[j].z);
			double dx = vp[i].x-vp[j].x;
			double dy = vp[i].y-vp[j].y;
			vl[i][j] = vl[j][i] = sqrt(dx*dx + dy*dy);
		}
	}
	
	double left = 0, right = 1e9;
	
	while (right - left > eps) {
		double mid = (left + right) / 2;
		if (check(mid)) right = mid;
		else left = mid;
	}
	
	printf("%.3lf\n", left);
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++) 
			scanf("%lf%lf%lf", &vp[i].x, &vp[i].y, &vp[i].z);
			
		solve();
	}
	
	return 0;
}

