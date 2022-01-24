// 201703-2 学生排队
/*
	思路：
	模拟
*/

#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> v;

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		v.push_back(i);

	int a, b;
	vector<int>::iterator it, nex;
	while(m--) {
		scanf("%d%d", &a, &b);

		for(it=v.begin(); it!=v.end(); it++) {
			if(*it == a) break;
		}

		nex = it + b;
		v.erase(it);
		v.insert(nex, a);
	}

	for(int i = 0; i < n; i++) {
		if(i != n-1)
			printf("%d ", v[i]);
		else
			printf("%d\n", v[i]);
	}

	return 0;
}
