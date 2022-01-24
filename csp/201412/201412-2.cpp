// Z字形扫描 - 201412-2
/*
问题描述
　　在图像编码的算法中，需要将一个给定的方形矩阵进行Z字形扫描(Zigzag Scan)。给定一个n×n的矩阵，Z字形扫描的过程如下图所示：

　　对于下面的4×4的矩阵，
　　1 5 3 9
　　3 7 5 6
　　9 4 6 4
　　7 3 1 3
　　对其进行Z字形扫描后得到长度为16的序列：
　　1 5 3 9 7 3 9 5 4 7 3 6 6 4 1 3
　　请实现一个Z字形扫描的程序，给定一个n×n的矩阵，输出对这个矩阵进行Z字形扫描的结果。
输入格式
　　输入的第一行包含一个整数n，表示矩阵的大小。
　　输入的第二行到第n+1行每行包含n个正整数，由空格分隔，表示给定的矩阵。
输出格式
　　输出一行，包含n×n个整数，由空格分隔，表示输入的矩阵经过Z字形扫描后的结果。
样例输入
4
1 5 3 9
3 7 5 6
9 4 6 4
7 3 1 3
样例输出
1 5 3 9 7 3 9 5 4 7 3 6 6 4 1 3
评测用例规模与约定
　　1≤n≤500，矩阵元素为不超过1000的正整数。
*/

#include <iostream>
#include <cstdio>

using namespace std;

const int dx[4] = {0, 1, 1, -1};	// right down l&d r&u
const int dy[4] = {1, 0, -1, 1};
const int maxn = 510;

int n;
int G[maxn][maxn];

// state l&d - 0 	r&u - 1
void dfs(int x, int y, bool state) {
	if(x == n-1 && y == n-1) {
		printf("%d\n", G[x][y]);
		return;
	}
	printf("%d ", G[x][y]);

	if(state) {
		if(x-1 >=0 && y+1 < n) {
			dfs(x-1, y+1, state);
		} else if(y+1 < n) {
			dfs(x, y+1, !state);
		} else if(x+1 < n) {
			dfs(x+1, y, !state);
		}
	} else {
		if(x+1 < n && y-1 >=0) {
			dfs(x+1, y-1, state);
		} else if(x+1 < n) {
			dfs(x+1, y, !state);
		} else if(y+1 < n) {
			dfs(x, y+1, !state);
		} 
	}
}

void solve() {
	printf("%d", G[0][0]);
	
	int x = 0, y = 0;
	while(1) {
		if(x == n-1 && y == n-1) break;
		
		if(y+1 < n) {
			y++;
			printf(" %d", G[x][y]);
		} else if(x+1 < n) {
			x++;
			printf(" %d", G[x][y]);
		}
		
		while(x+1 < n && y-1 >= 0) {
			x++; y--;
			printf(" %d", G[x][y]);
		}
		
		if(x+1 < n) {
			x++;
			printf(" %d", G[x][y]);
		} else if(y+1 < n) {
			y++;
			printf(" %d", G[x][y]);
		} 
		
		while(x-1 >= 0 && y+1 < n) {
			x--; y++;
			printf(" %d", G[x][y]);
		}
	}
	printf("\n");
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &G[i][j]);
		}
	}
//	dfs(0, 0, 1);
	solve();

	return 0;
}
