// HDU 3038 How Many Answers Are Wrong
// Disjoint Set
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 2e5+10;
int n,m,ans;
int sum[maxn];							// 到根节点的矢量和
int pa[maxn];

void init() {
	for(int i=0; i<=n; i++) {
		pa[i] = i;
		sum[i] = 0;
	}
}

int find(int x) {
	if(x == pa[x])
		return x;
	int temp = pa[x];
	pa[x] = find(temp);					// 压缩路径
	sum[x] = sum[temp]+sum[x];			// 计算矢量和
	return pa[x];
}

void join(int x,int y,int w) {
	int x_r,y_r;
	x_r = find(x);
	y_r = find(y);
	if(x_r == y_r) {
		if(w != sum[x]-sum[y])
			ans++;
	} else {
		pa[x_r] = y_r;
		sum[x_r] = -sum[x]+w+sum[y];
	}
}

int main() {
	while(cin >> n >> m) {
		init();
		int x,y,w;
		ans = 0;
		while(m--) {
			scanf("%d%d%d",&x,&y,&w);
			x--;
			join(x,y,w);
		}
		cout << ans << endl;
	}

	return 0;
}

