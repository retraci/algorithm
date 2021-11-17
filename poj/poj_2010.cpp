// POJ 2010 Moo University - Financial Aid
/*
	思路：
	优先队列 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;

const int INF = 0x3f3f3f3f;
const int maxn = 100010;

ll n, m, f;
P cs[maxn];

void solve() {
	priority_queue<int> que1, que2;
	ll f1[maxn], f2[maxn];
	memset(f1, 0, sizeof(f1));
	memset(f2, 0, sizeof(f2));
	sort(cs, cs+m);

	ll sum1 = 0, sum2 = 0;
	for(int i = 0; i < m; i++) {
		if(que1.size() < n/2) {
			que1.push(cs[i].second);
			sum1 += cs[i].second;
			continue;
		}

		f1[i] = sum1;
		
		if(cs[i].second >= que1.top()) continue;
		sum1 -= que1.top(); que1.pop();
		que1.push(cs[i].second);
		sum1 += cs[i].second;
	}
	
	for(int i = m-1; i >= 0; i--) {
		if(que2.size() < n/2) {
			que2.push(cs[i].second);
			sum2 += cs[i].second;
			continue;
		}

		f2[i] = sum2;
		
		if(cs[i].second >= que2.top()) continue;
		sum2 -= que2.top(); que2.pop();
		que2.push(cs[i].second);
		sum2 += cs[i].second;
	}
	for(int i = m-1; i >= 0; i--) {
		if(f1[i] && f2[i] && f1[i]+f2[i]+cs[i].second <= f) {
			cout << cs[i].first << endl;
			return;
		}
	}
	cout << -1 << endl;
}

int main() {
	cin >> n >> m >> f;
	for(int i = 0; i < m; i++) {
		scanf("%I64d%I64d", &cs[i].first, &cs[i].second);
	}
	solve();

	return 0;
}
