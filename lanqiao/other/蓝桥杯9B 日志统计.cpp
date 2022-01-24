// 蓝桥杯9B 日志统计
/*
	思路：
	遍历，尺取法 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;

int n, d, k;
vector<int> logs[maxn];
set<int> blogs;

void solve() {
	vector<int> ans;

	set<int>::iterator it;
	for(it=blogs.begin(); it!=blogs.end(); it++) {
		sort(logs[*it].begin(), logs[*it].end());
		int len = logs[*it].size();
		int l = 0, r = 0, flag = 0;

		while(r < len) {
			if(r-l+1 >= k) {
				if(logs[*it][r]-logs[*it][l] < d) {
					flag = 1;
					break;
				} else {
					l++;
				}
			}
			r++;
		}

		if(flag) ans.push_back(*it);
	}

	for(int i = 0; i < ans.size(); i++) {
		printf("%d\n", ans[i]);
	}
}

int main() {
	cin >> n >> d >> k;

	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		logs[b].push_back(a);
		blogs.insert(b);
	}

	solve();

	return 0;
}
