// POJ 3279 Fliptile (翻黑白棋
// 枚举 (二进制枚举
#include <iostream>
#include <cstdio>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace std;

const int maxn = 20;

int n,m,cnt;
int map[maxn][maxn];		// 输入的地图
int cal[maxn][maxn];		// 操作
int out[maxn][maxn];		// 保存输出的操作
int dx[] = {0,1,-1,0,0};
int dy[] = {0,0,0,1,-1};

int isBlack(int x,int y) {
	int temp = map[x][y];

	int nx,ny;
	// 自己的状态加自己以及附近 5个方块的操作，即为当前状态 
	for(int i=0; i<5; i++) {
		nx = x+dx[i];
		ny = y+dy[i];
		if(nx<1 || nx>n || ny<1 || ny>m) continue;
		temp += cal[nx][ny];
	}

	return temp%2;
}

// 上一行的为黑色，下一行必定要翻，二进制枚举第一行的所有情况，每一行递推 
int solve() {
	for(int i=2; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(isBlack(i-1,j))
				cal[i][j] = 1;
		}
	}

	for(int j=1; j<=m; j++) {
		if(isBlack(n,j))
			return -1;
	}

	int ret = 0;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			ret += cal[i][j];
		}
	}
	
	return ret;
}

int main() {
	while(cin >> n >> m) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				cin >> map[i][j];
			}
		}
		cnt = INF;
		for(int i=0; i<(1<<m); i++) {			// 二进制枚举第一行操作
			memset(cal,0,sizeof(cal));
			for(int j=0; j<m; j++) {
				cal[1][m-j] = 1 & (i>>j);
			}
//			for(int j=1;j<=m;j++) 
//				cout << cal[1][j] << " ";
//			cout << endl;

			int ret = solve();
			if(ret!=-1 && ret<cnt) {
				cnt = ret;
				memcpy(out,cal,sizeof(cal));
			}
		}
		if(cnt == INF) {
			cout<<"IMPOSSIBLE"<<endl;
		} else {
//			cout << cnt << endl;
			for(int i=1; i<=n; i++) {
				for(int j=1; j<=m; j++) {
					if(j != 1) cout << " ";
					cout << out[i][j];
				}
				cout << endl;
			}
		}
	}

	return 0;
}

