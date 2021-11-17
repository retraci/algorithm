// POJ 3660 Cow Contest
// Floyd -- 每个点与其他点之间的关系 
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 110;
int n,m;
int dis[maxn][maxn]; 

void Floyd() {
	for(int k=1; k<=n; k++) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				dis[i][j] = dis[i][j] || (dis[i][k] && dis[k][j]);
			}
		}
	}
}

int main() {
	int a,b;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		cin >> a >> b;
		dis[a][b] = 1;
	}
	Floyd();
	int cnt=0,ans=0;
	for(int i=1; i<=n; i++) {
		cnt = 0;
		for(int j=1; j<=n; j++) {
			if(i==j) continue;
			if(dis[i][j] || dis[j][i]) cnt++;
		}
		if(cnt==n-1) ans++;
	}
	cout << ans;
	
	return 0;
}
