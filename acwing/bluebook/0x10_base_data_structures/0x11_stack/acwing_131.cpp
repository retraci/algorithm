#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 100010;

int n;
ll va[N];
ll lb[N], rb[N];

void solve() {
    vector<int> stk;

    for (int i = 0; i < n; i++) {
        while (stk.size() && va[i] <= va[stk.back()]) stk.pop_back();
        lb[i] = stk.size() ? stk.back() : -1;
        stk.push_back(i);
    }

    stk.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (stk.size() && va[i] <= va[stk.back()]) stk.pop_back();
        rb[i] = stk.size() ? stk.back() : n;
        stk.push_back(i);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll h = va[i];
        ll w = rb[i] - lb[i] - 1;
        ans = max(ans, h * w);
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    while (cin >> n, n) {
        for (int i = 0; i < n; i++) scanf("%lld", &va[i]);
        solve();
    }

    return 0;
}