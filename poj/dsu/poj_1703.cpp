// POJ 1703 Find them, Catch them
/*
	思路：
	不同集合的 并查集 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxn = 1e5+10;

int n, m;
int fa[maxn*2];

int find(int x) {
	return x==fa[x]? x : fa[x] = find(fa[x]);
}

int main() {
	char ch;
	int a, b;
	int T;
	cin >> T;
	
	while(T--) {
		cin >> n >> m;
		for(int i = 0; i <= 2*n; i++) fa[i] = i;
		
		while(m--) {
			cin >> ch;
			scanf("%d%d", &a, &b);
			int tx1 = find(a);
			int ty1 = find(b);
			int tx2 = find(a+n);
			int ty2 = find(b+n);
			
			if(ch == 'D') {
				if(tx1 != ty2) {
					fa[tx1] = ty2;
				}
				if(tx2 != ty1) {
					fa[tx2] = ty1;
				}
			} else {
				if(tx1 == ty1) {
					cout << "In the same gang." << endl;
				} else if(tx1 == ty2) {
					cout << "In different gangs." << endl;
				} else {
					cout << "Not sure yet." << endl;
				}
			}			
		}

	}
	
	return 0;
}
