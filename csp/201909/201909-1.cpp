// 201909-1
/*
	思路：
	 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

int n, m;
int a[maxn], b[maxn];

int main() {
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			if(j == 0) {
				scanf("%d", &a[i]);
				continue;
			}
			int temp;
			scanf("%d", &temp);
			b[i] += temp;
		}
	}
	
	int mx = b[1];
	int idx = 1;
	for(int i = 2; i <= n; i++) {
		if(mx > b[i]) {
			mx = b[i];
			idx = i;
		}
	}
	
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i] + b[i];
	}
	
	printf("%d %d %d\n", sum, idx, -mx);
	
	return 0;
}
