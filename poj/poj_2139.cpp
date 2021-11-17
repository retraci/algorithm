// POJ 2139 Six Degrees of Cowvin Bacon
/*
	思路：
	Floyd 
	
	node:
	图用 矩阵
	计算 k->i->j 
	计算直接用 graph矩阵 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 310;

int n, m;
int graph[maxn][maxn];

void solve() {
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
			}
		}
	}
//	cout << endl;
//	for(int i = 1; i <= n; i++) {
//		for(int j = 1; j <= n; j++) {
//			printf("%d ", graph[i][j]);
//		}
//		cout << endl;
//	}

	int ans = INF;
	int sum;
	for(int i = 1; i <= n; i++) {
		sum = 0;
		for(int j = 1; j <= n; j++) {
			sum += graph[i][j];
		}
		ans = min(ans, 100*sum/(n-1));
	}

	printf("%d\n", ans);
}

int main() {
	cin >> n >> m;
	memset(graph, INF, sizeof(graph));
	for(int i = 1; i <= n; i++) graph[i][i] = 0;

	vector<int> temp;
	while(m--) {
		int cnt, t;
		scanf("%d", &cnt);

		temp.clear();
		for(int i = 0; i < cnt; i++) {
			scanf("%d", &t);
			temp.push_back(t);
		}
		for(int i = 0; i < cnt; i++) {
			for(int j = i+1; j < cnt; j++) {
				graph[temp[i]][temp[j]] = 1;
				graph[temp[j]][temp[i]] = 1;
			}
		}
	}

//	cout << endl;
//	for(int i = 1; i <= n; i++) {
//		for(int j = 1; j <= n; j++) {
//			printf("%d ", graph[i][j]);
//		}
//		cout << endl;
//	}

	solve();

	return 0;
}
