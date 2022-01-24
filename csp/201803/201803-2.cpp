// 201803-2
/*
	思路：
	模拟
	
	node:
	先维护速度，再维护位置 
*/

#include <bits/stdc++.h>

using namespace std;

int n, len, t;
vector<int> xs[2], vs[2];

/*
2 4 5
0 4
*/

void solve() {
	xs[1].resize(n);
	vs[1].resize(n);
	for(int i = 0; i < t; i++) {
		for(int j = 0; j < n; j++) {
			vs[(i+1)%2][j] = vs[i%2][j];
		}
		for(int j = 0; j < n; j++) {
			for(int k = j+1; k < n; k++) {
				if(xs[i%2][j] == xs[i%2][k]) {
					vs[(i+1)%2][j] = -vs[i%2][j];
					vs[(i+1)%2][k] = -vs[i%2][k];
					break;
				}
			}
			if(xs[i%2][j] == 0) {
				vs[(i+1)%2][j] = 1;
			} else if (xs[i%2][j] == len) {
				vs[(i+1)%2][j] = -1;
			}
		}
		for(int j = 0; j < n; j++) {
			xs[(i+1)%2][j] = xs[i%2][j] + vs[(i+1)%2][j];
		}
		/*
		cout << endl;
		for(int j = 0; j < n; j++) {
			if(j != n-1)
				printf("%d ", xs[(i+1)%2][j]);
			else 
				printf("%d\n", xs[(i+1)%2][j]);
		}
		*/
	}
	
	
	for(int j = 0; j < n; j++) {
		if(j != n-1)
			printf("%d ", xs[t%2][j]);
		else 
			printf("%d\n", xs[t%2][j]);
	}
	
}

int main() {
	cin >> n >> len >> t;
	
	int temp;
	for(int i = 0; i < n; i++) {
		scanf("%d", &temp);
		xs[0].push_back(temp);
		vs[0].push_back(1);
	}
	solve();
	
	return 0;
} 
