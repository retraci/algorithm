// POJ 2253 Frogger
// Floyd
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define INF 0x3f3f3f3f
using namespace std;

struct Point {
	int x,y;

	Point() {
	}
	Point(int xx,int yy):x(xx),y(yy) {
	}
};

const int maxn = 210;
Point P[maxn];
double dis[maxn][maxn];						// 多源，所以用二维数组 
int n;

void Floyd() {
	for(int k=1; k<=n; k++) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				// i --> j 共有两条路径 ：i --> j 与 i --> k --> j 
				// 选择两个路径中最短的一个跳跃距离 
				dis[i][j] = min(dis[i][j],max(dis[i][k],dis[k][j]));
			}
		}
	}
}

int main() {
	int x,y;
	int casee = 1;
	while(cin>>n && n!=0) {
		for(int i=1; i<=n; i++) {
			cin >> x >> y;
			P[i] = Point(x,y);
		}
		double cost;
		for(int i=1; i<=n; i++) {
			for(int j=i+1; j<=n; j++) {
				cost = (P[i].x-P[j].x)*(P[i].x-P[j].x)+(P[i].y-P[j].y)*(P[i].y-P[j].y);
				cost = sqrt(cost);
				dis[i][j] = dis[j][i] = cost;
			}
		}
		Floyd();
		printf("Scenario #%d\n",casee++);
		printf("Frog Distance = %.3f\n\n",dis[1][2]);
	}

	return 0;
}


