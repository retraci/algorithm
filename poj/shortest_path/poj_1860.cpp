// POJ 1860 Currency Exchange
// Bellman Ford
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110;

struct Edge {
	int from,to;
	double r,c;
} edge[maxn*maxn];

int n,m,s;						// s 当前的货币种类
double v;						// 当前的货币总额
double dis[maxn];

bool Bellman() {
	memset(dis,0,sizeof(dis));
	dis[s] = v;
	int flag = 0;
	for(int i=0; i<n-1; i++) {
		flag = 0;
		for(int j=0; j<m; j++) {
			if(dis[edge[j].to] < (dis[edge[j].from]-edge[j].c)*edge[j].r) {
				dis[edge[j].to] = (dis[edge[j].from]-edge[j].c)*edge[j].r;
				flag = 1;
			}
		}
		if(!flag)
			return true;
	}

	for(int j=0; j<m; j++) {
		if(dis[edge[j].to] < (dis[edge[j].from]-edge[j].c)*edge[j].r)
			return false;
	}

	return true;
}

int main() {
	int a,b;
	double ra,ca,rb,cb;
	while(cin >> n >> m >> s >> v) {
		for(int i=0; i<m; i++) {
			cin >> a >> b >> ra >> ca >> rb >> cb;
			edge[2*i].from = a;
			edge[2*i].to = b;
			edge[2*i].r = ra;
			edge[2*i].c = ca;
			edge[2*i+1].from = b;
			edge[2*i+1].to = a;
			edge[2*i+1].r = rb;
			edge[2*i+1].c = cb;
		}

		m *= 2;
		if(Bellman()) {
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
		}
	}

	return 0;
}

