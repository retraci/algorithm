#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

#define ll long long

ll a, b, n;

bool check(ll md) {
    ll c = md / 7, r = md % 7;
    ll round = 5 * a + 2 * b;
    ll nd = (n + round - 1) / round;
    if (nd <= c) return true;

    ll s = c * round;
    for (int i = 1; i <= r; i++) {
        if (i <= 5) s += a;
        else s += b;
        if (s >= n) break;
    }

    return s >= n;
}

void solve() {
    ll left = 0, right = 1e18;
    while (left < right) {
        ll md = left + right >> 1;
        if (check(md)) right = md;
        else left = md + 1;
    }
    cout << left << "\n";
}

int main() {
//    freopen("../in.txt", "r", stdin);
    freopen("../dp.in", "r", stdin);
    freopen("../out.txt", "w", stdout);

    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b >> n;
        solve();
    }

	return 0;
}
