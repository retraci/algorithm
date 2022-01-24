// luogu_P2872
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

#define MAX_SIZE 1000
#define MAX_WEIGHT 0x7fffffff

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	point vexs[MAX_SIZE];
	double arcs[MAX_SIZE][MAX_SIZE];
	int arcnum;
	int vexnum;
} Graph;

int N,M;
Graph G;
double ans;

double js_dis(point p1,point p2) {
	return sqrt(pow(double(p1.x-p2.x),2)+pow(double(p1.y-p2.y),2));
}

void Prim() {
	double lowcast[MAX_SIZE];
	int n = G.vexnum;

	memset(lowcast,MAX_WEIGHT,sizeof(lowcast));
	for(int i=1; i<n; i++) {
		lowcast[i] = G.arcs[0][i];
	}
	lowcast[0] = -1;		//标记

	double minWeight;
	int k;
	for(int v=1; v<n; v++) {
		
		minWeight = MAX_WEIGHT;
		for(int i=1; i<n; i++) {
			if(lowcast[i]>=0 && minWeight>lowcast[i]) {
				k = i;
				minWeight = lowcast[i];
			}
		}

		ans += minWeight;
		lowcast[k] = -1;
		for(int i=1; i<n; i++) {
			if(lowcast[i]>=0 && lowcast[i]>G.arcs[k][i]) lowcast[i] = G.arcs[k][i];
		}
	}
}

int main() {
	cin >> N >> M;

	G.vexnum = N;
	for(int i=0; i<G.vexnum; i++) {
		cin >> G.vexs[i].x >> G.vexs[i].y;
	}

	for(int i=0; i<G.vexnum; i++) {
		for(int j=0; j<G.vexnum; j++) {
			G.arcs[i][j] = G.arcs[j][i] = js_dis(G.vexs[i],G.vexs[j]);
		}
	}

	for(int k=0; k<M; k++) {
		int i,j;
		cin >> i >> j;
		G.arcs[i-1][j-1] =G.arcs[j-1][i-1] = 0;
	}

	Prim();
	printf("%.2lf",ans);

	return 0;
}
