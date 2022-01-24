// 合并石子
/*

*/

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;

void solve() {
	int cnt = 0;
	while (i < v.size()) {
		if (v[i] >= v[i-1]) continue;
		
		int tmp1;
		if (i == v.size()-1) tmp1 = v[i];
		else tmp1 = v[i] + v[i+1];
		
		if (tmp1 >= v[i-1]) {
			v[i] = tmp1;
			v.erase(i-1);
		} else if (tmp2 >= v[i-1]) {
			v[i] = tmp2;
			if (i+1 < v.size()) v.erase(i+1);
		} else {
			
		}
		
		cnt++;
	}
}

int main() {
	cin >> n;
	
	int tmp;
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		v.push_back(tmp);
	}
	solve();
	
	return 0;
} 
