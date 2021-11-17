// POJ 3262 Protecting the Flowers
/*
	思路：
	贪心，优先 cost/time 大的 
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

struct cow {
	ll time, cost;
	cow(ll t, ll c):time(t),cost(c) {
	}
};

ll n, ans;
vector<cow> cows;
vector<ll> pre_sum;

bool cmp(cow c1, cow c2) {
	return (double)c1.cost/c1.time > (double)c2.cost/c2.time; 
}

void solve() {
	sort(cows.begin(), cows.end(), cmp);
	pre_sum.resize(n);

	pre_sum[n-1] = 0;
	for(int i = n-2; i >= 0; i--) {
		pre_sum[i] = pre_sum[i+1]+cows[i+1].cost;
	}
	for(int i = 0; i < n; i++) {
		ans += pre_sum[i]*cows[i].time*2;
	}
	cout << ans << endl;
}

int main() {
	cin >> n;
	int t1, t2;
	for(int i = 0; i < n; i++) {
		scanf("%ld %ld", &t1, &t2);
		cows.push_back(cow(t1, t2));
	}
	solve();

	return 0;
}
