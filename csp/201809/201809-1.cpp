// 201809-1
/*
	思路:
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;

void solve() {
	
	for(int i = 0; i < n; i++) {
		int temp;
		if(i == 0) {
			temp = (v[0] + v[1]) / 2;
			printf("%d ", temp);
		} else if(i == n-1) {
			temp = (v[n-1] + v[n-2]) / 2;
			printf("%d\n", temp);
		} else {
			temp = (v[i-1] + v[i] + v[i+1]) / 3;
			printf("%d ", temp);
		}
		
	}
}

int main() {
	cin >> n;
	
	int temp;
	for(int i = 0; i < n; i++) {
		scanf("%d", &temp);
		v.push_back(temp);
	}
	solve();
	
	return 0;
}
