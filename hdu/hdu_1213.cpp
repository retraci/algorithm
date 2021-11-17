// HDU 1213 How Many Tables
// disjoint set
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1e3+10;
int m,n,ans;
int parent[maxn];
int rankk[maxn];

int find(int x) {
	int x_root = x;
	while(parent[x_root] != -1) {
		x_root = parent[x_root];
	}
	return x_root;
}

void join(int x,int y) {
	int x_root = find(x);
	int y_root = find(y);
	
	if(x_root == y_root) return;
	if(rankk[x_root] > rankk[y_root]) {
		parent[y_root] = x_root;
	} else if(rankk[y_root] > rankk[x_root]) {
		parent[x_root] = y_root;

	} else {
		parent[x_root] = y_root;
		rankk[y_root]++;
	}	
	ans--;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> m;
		int a,b;
		ans = n;
		memset(parent,-1,sizeof(parent));
		memset(rankk,0,sizeof(rankk));
		for(int i=0; i<m; i++) {
			cin >> a >> b;
			join(a,b);
		}
		cout << ans << endl;
	}

	return 0;
}

