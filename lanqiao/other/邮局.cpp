// 蓝桥杯 邮局
/*
	思路：
	dfs + 剪枝
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

struct point {
	int x, y;
	point(int xx, int yy):x(xx), y(yy) {
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 55;
const int maxm = 30;

int n, m, k;
vector<point> peo;
vector<point> post;
double mp[maxn][maxm];

double res;
vector<int> path;
int flag[maxm];

double dis(point p1, point p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

void dfs(int s, int sum_k, double sum_dis, vector<double> dist, vector<int> cur) {
//	printf("\n%d %d\n", s, sum_k);
//	cout << sum_dis << endl;
//	for(int i = 0; i < n; i++) {
//		printf("%lf ", dist[i]);
//	}
//	cout << endl;
	if(sum_k == k) {
		if(sum_dis < res) {
			res = sum_dis;
			path.insert(path.begin(), cur.begin(), cur.end());
			return;
		}
	}

	// 可选 + 已选 >= k
	// 不选 s
	if(s+1 <= m && m-s+sum_k >= k && sum_k <= k)
		dfs(s+1, sum_k, sum_dis, dist, cur);

	// 如果 s 不能减少距离
	if(flag[s]) return;
	cur[sum_k] = (s+1);

	int mark1 = 0, mark2 = 0;
	if(sum_k == 0) {
		sum_dis = 0;
		for(int i = 0; i < n; i++) {
			dist[i] = mp[i][s];
			sum_dis += dist[i];
		}
		mark1 = 1;
	} else {
		for(int i = 0; i < n; i++) {
			if(dist[i] > mp[i][s]) {
				mark2 = 1;
				sum_dis += mp[i][s]-dist[i];
//				if(!sum_dis) printf("%d %d\n", i, s);
				dist[i] = mp[i][s];
			}
		}
	}
	if(!mark1 && !mark2) {
		flag[s] = 1;
	} else {
		if(s+1 <= m && m-s+sum_k+1 >= k && sum_k+1 <= k) {
			dfs(s+1, sum_k+1, sum_dis, dist, cur);
		}
	}
}

void solve() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			mp[i][j] = dis(peo[i], post[j]);
		}
	}
//	for(int i = 0; i < n; i++) {
//		for(int j = 0; j < m; j++) {
//			printf("%lf ", mp[i][j]);
//		}
//		cout << endl;
//	}

	res = INF;
	memset(flag, 0, sizeof(flag));
	vector<double> dist(n, INF);
	vector<int> cur(k);

	dfs(0, 0, INF, dist, cur);

//	cout << path.size() << endl;
	for(int i = 0; i < k; i++) {
		if(i != k-1)
			printf("%d ", path[i]);
		else
			printf("%d\n", path[i]);
	}
}

int main() {
	cin >> n >> m >> k;

	int x, y;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &x, &y);
		peo.push_back(point(x, y));
	}
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		post.push_back(point(x, y));
	}
	solve();

	return 0;
}
