// POJ 3616 Miking Time 
/*
	思路：
	dp[i] 表示选择 i 并且前 i 的时间表的最大值
	初始化 dp[i] = schs[i].e 
	遍历 i 之前选过的时间表，拿最大值加上 i 自身 
	最后遍历 dp 数组获取最大值
	
	ps：不使用 n 进行递推，原因是 时间 之间的递推关系不好，
	需要对比 时间表 之间的开始结束时间，因此直接使用 m 进行递推 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct sch {
	int s, t, e;
};

const int maxm = 1010;

int n, m, r;
int dp[maxm];
sch schs[maxm];

bool cmp(sch s1, sch s2) {
	return s1.t < s2.t;
}

void solve() {
	sort(schs+1, schs+m+1, cmp);
	
	for(int i = 1; i <= m; i++) {
		dp[i] = schs[i].e;
		for(int j = 1; j <= i; j++) {
			if(schs[i].s >= r+schs[j].t) {
				dp[i] = max(dp[i], schs[i].e+dp[j]);
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= m; i++) ans = max(ans, dp[i]);
	cout << ans << endl;
}

int main() {
	cin >> n >> m >> r;
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%d", &schs[i].s, &schs[i].t, &schs[i].e);
	}
	solve();
	
	return 0;
}
