// 201604-2
/*
	思路：
	模拟
*/

#include <bits/stdc++.h>

using namespace std;

int a[20][20];
int b[5][5];
int c;

bool is_vaild(int k) {
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(b[i][j] == 0) continue;
			if(k+i-1 > 15) return false;
			if(a[k+i-1][c+j-1] == 1) return false;
		}
	}
	return true;
}

void solve() {
	int layer;
	for(int k = 1; k <= 15; k++) {
		if(is_vaild(k)) {
			layer = k;
		} else {
			break;
		}
	}

	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(b[i][j])
				a[layer+i-1][c+j-1] = b[i][j];
		}
	}

	for(int i = 1; i <= 15; i++) {
		for(int j = 1; j <= 10; j++) {
			printf("%d ", a[i][j]);
		}
		cout << endl;
	}
}

int main() {
	for(int i = 1; i <= 15; i++) {
		for(int j = 1; j <= 10; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			scanf("%d", &b[i][j]);
		}
	}
	cin >> c;
	solve();

	return 0;
}
