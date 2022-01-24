// luogu_P2213
#include <iostream>
using namespace std;

#define MAX_N 400

int N,K;
int ans;
int G[MAX_N+1][MAX_N+1];
int map[MAX_N*2][MAX_N*2];

int main() {
	cin >> N >> K;

	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			cin >> G[i][j];
		}
	}
	
	// 转矩阵
	int n = N*2-1;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			map[i+j-1][N-i+j] = G[i][j];
		}
	}

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++){
			map[i][j] += map[i][j-1];
		}
	}

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++){
			map[i][j] += map[i-1][j];
		}
	}
	
	/*
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			int ni = i+j-1;
			int nj = N-i+j;

			int x1 = ni-K;
			int y1 = nj-K;
			int x2 = ni+K;
			int y2 = nj+K;

			if(x1<1) x1 = 1;
			if(y1<1) y1 = 1;
			if(x2>n) x2 = n;
			if(y2>n) y2 = n;
			
			int t = map[x2][y2]-map[x2][y1-1]-map[x1-1][y2]+map[x1-1][y1-1];
			ans = t>ans?t:ans;

		}
	}
	
	/*
	int m=N*2-1;//新矩阵的大小
	for(int i=1; i<=N; i++)
		for(int j=1; j<=N; j++)
			map[i+j-1][N-i+j]=G[i][j];//把矩阵旋转过来
	for(int i=1; i<=m; i++)
		for(int j=1; j<=m; j++)
			map[i][j]+=map[i][j-1];//前缀和
	for(int j=1; j<=m; j++)
		for(int i=1; i<=m; i++)
			map[j][i]+=map[j-1][i];//前缀和
	for(int i=1; i<=N; i++)
		for(int j=1; j<=N; j++) {
			int x=i+j-1,y=N-i+j;//求旋转后的坐标
			int xl=x-K,yl=y-K,xr=x+K,yr=y+K;//求左上角、右下角的坐标
			if(xl<1) xl=1;
			if(yl<1) yl=1;
			if(xr>m) xr=m;
			if(yr>m) yr=m;//超出矩阵外的部分要去掉
			ans=max(ans,map[xr][yr]-map[xr][yl-1]-map[xl-1][yr]+map[xl-1][yl-1]);//更新答案
		}
	*/	
	
		
	cout << ans;

	return 0;
}
