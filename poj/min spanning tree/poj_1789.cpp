// POJ 1789 Truck History
// Kruskal / Prim
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace std;

const int maxn = 2010;

/*
struct Edge {
	int from,to,w;
} edge[maxn*maxn];
*/

struct Node {
	int to,w;

	Node(int tt,int ww):to(tt),w(ww) {
	}
	bool operator < (const Node &a) const {
		return w > a.w;
	}
};

int n,m;
char ss[maxn][10];
//int pa[maxn];

int dis[maxn];
bool vis[maxn];
vector<Node> G[maxn];

//bool cmp(Edge &a,Edge &b) {
//	return a.w < b.w;
//}
//
int get_w(char* a,char* b) {
	int ret = 0;
	for(int i=0; a[i]; i++) {
		if(a[i] != b[i])
			ret++;
	}

	return ret;
}
//
//void init() {
//	for(int i=0; i<n; i++)
//		pa[i] = i;
//}
//
//int find(int x) {
//	if(x == pa[x])
//		return x;
//	int temp = pa[x];
//	pa[x] = find(temp);
//	return pa[x];
//}
//
//bool join(int x,int y) {
//	int rx = find(x);
//	int ry = find(y);
//	if(rx == ry)
//		return false;
//	else
//		pa[rx] = ry;
//
//	return true;
//}
//
//int Kruskal() {
//	sort(edge,edge+m,cmp);
//	int cnt = 0;
//	int ans = 0;
//	for(int i=0; i<m; i++) {
//		if(join(edge[i].from,edge[i].to)) {
//			ans += edge[i].w;
//			cnt++;
//		}
//		if(cnt == n-1)
//			break;
//	}
//
//	return ans;
//}

int Prim() {
	priority_queue<Node> q;
	memset(dis,INF,sizeof(dis));
	memset(vis,false,sizeof(vis));
	int ans = 0;
	dis[0] = 0;
	q.push(Node(0,dis[0]));
	while(!q.empty()) {
		Node t = q.top();
		q.pop();
		int u = t.to;
		if(vis[u]) continue;
		vis[u] = true;
		ans += dis[u];

		for(int i=0; i<G[u].size(); i++) {
			Node temp = G[u][i];
			int v = temp.to;
			int w = temp.w;
			if(dis[v] > w) {
				dis[v] = w;
				q.push(Node(v,dis[v]));
			}
		}
	}

	return ans;
}

int main() {
	while(scanf("%d",&n) != EOF) {
		if(n == 0) break;
		for(int i=0; i<n; i++) {
			scanf("%s",ss[i]);
		}
		int temp;
		// ³õÊ¼»¯ G 
		for(int i=0;i<n;i++)
			G[i].clear();
		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				temp = get_w(ss[i],ss[j]);
				G[i].push_back(Node(j,temp));
				G[j].push_back(Node(i,temp));
			}
		}

		cout << "The highest possible quality is 1/" << Prim() << "." << endl;
	}

	return 0;
}

/*
int main() {
	while(scanf("%d",&n) != EOF) {
		if(n == 0) break;
		init();
		m = 0;
		for(int i=0; i<n; i++) {
			scanf("%s",ss[i]);
//			cout << ss[i] << endl;
		}

		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				edge[m].from = i;
				edge[m].to = j;
				edge[m].w = get_w(ss[i],ss[j]);
				m++;
//				edge[m].from = j;
//				edge[m].to = i;
//				edge[m].w = temp;
//				m++;
//				cout << temp << " ";
			}
		}
		cout << "The highest possible quality is 1/" << Kruskal() << "." << endl;
	}

	return 0;
}
*/


