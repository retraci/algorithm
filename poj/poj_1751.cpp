// POJ 1751 Highways
// Prim / Kruskal
// 初始有边的时候，Prim用邻接矩阵，Kruskal不用 cnt 
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace std;

const int maxn = 760;

/*
struct Point {
	int x,y;
} point[maxn];

struct Node {
	int from,to;
	double w;
	Node(int ff,int tt,double ww):from(ff),to(tt),w(ww){
	}
	bool operator < (const Node &t) const {
		return w > t.w;
	}
};

double mp[maxn][maxn];
int n,m;
double dis[maxn];
bool vis[maxn];

void init() {
	for(int i=0;i<=n;i++) {
		vis[i] = false;
		dis[i] = 1e7;
	}
}

double get_dist(int a,int b) {
	double temp = (point[a].x-point[b].x)*(point[a].x-point[b].x)+(point[a].y-point[b].y)*(point[a].y-point[b].y);
	return sqrt(temp);
}

void Prim() {
	priority_queue<Node> q;
	q.push(Node(1,1,-1));
	dis[1] = 0;
	while(!q.empty()) {
		Node t = q.top();
		q.pop();
		if(vis[t.to]) continue;
		vis[t.to] = true;
		if(dis[t.to])
			cout << t.from << " " << t.to << endl;
			
		int from,to;
		double w;
		for(int i=1;i<=n;i++) {
			from = t.to;
			to = i;
			w = mp[from][to];
//			cout << from << " " << to << " " << w << endl;
//			cout << dis[to] << endl;
			if(!vis[to] && dis[to] > w) {
				dis[to] = w;
				q.push(Node(from,to,w));
			}
		}
//		cout << endl;
	}
}

int main() {
	cin >> n;
	init();
	for(int i=1;i<=n;i++) {
		cin >> point[i].x >> point[i].y;
	}
		
	double w;
	for(int i=1;i<=n;i++) {
		for(int j=i+1;j<=n;j++) {
			w = get_dist(i,j);
			mp[i][j] = mp[j][i] = w;
		}
	}
	
	cin >> m;
	int a,b;
	for(int i=0;i<m;i++) {
		cin >> a >> b;
		mp[a][b] = 0;
		mp[b][a] = 0;
	}
	
	Prim();
	
	return 0;
}
*/


struct Node {
	int x,y;
} node[maxn];

struct Edge {
	int from,to;
	double w;
} edge[maxn*maxn];

int n,m,len,pa[maxn];
vector<int> ans;

bool cmp(Edge a,Edge b) {
	return a.w < b.w;
}

double get_dist(int a,int b) {
	double temp = (node[a].x-node[b].x)*(node[a].x-node[b].x)+(node[a].y-node[b].y)*(node[a].y-node[b].y);
	return sqrt(temp);
}

void init() {
	for(int i=0;i<=n;i++) 
		pa[i] = i;
}

int find(int x) {
	if(x == pa[x]) return x;
	int temp = pa[x];
	pa[x] = find(temp);
	return pa[x];
}

bool join(int a,int b) {
	int ra = find(a);
	int rb = find(b);
	if(ra == rb) return false;
	else {
		pa[ra] = rb;
		return true;
	}
}

void Kruskal() {
	sort(edge,edge+len,cmp);
//	for(int i=0;i<len;i++) cout << edge[i].w << endl;
//	int cnt = 0;
	for(int i=0;i<len;i++) {
		if(join(edge[i].from,edge[i].to)) {
			ans.push_back(i);
//			cnt++;
		}
//		if(cnt == n-1-m) break;
	}
//	cout << cnt << endl;
}

int main() {
	cin >> n;
	init();
	for(int i=1;i<=n;i++) {
		cin >> node[i].x >> node[i].y;
	}
	
	cin >> m;
	int a,b;
	for(int i=0;i<m;i++) {
		cin >> a >> b;
		join(a,b);
	}
	
//	for(int i=0;i<=n;i++) cout << pa[i] << endl;
	
	len = 0;
	for(int i=1;i<=n;i++) {
		for(int j=i+1;j<=n;j++) {
			edge[len].from = i;
			edge[len].to = j;
			edge[len].w = get_dist(i,j);
			len++;
		}
	}
	
	Kruskal();
	int index;
	for(int i=0;i<ans.size();i++) {
		index = ans[i];
		cout << edge[index].from << " " << edge[index].to << endl;
	}
	
	return 0;
}

