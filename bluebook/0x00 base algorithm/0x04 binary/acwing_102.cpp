#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define ll long long

const int maxn = 100010;

int n, m;
long long va[maxn], vs[maxn];

bool check(ll mid) {
    for (int i = 1; i <= n; i++) {
        vs[i] = va[i] - mid;
        vs[i] += vs[i-1];
    }

    ll minVal = 1e9, ans = -1e9;
    for (int i = m; i <= n; i++) {
        minVal = min(minVal, vs[i - m]);
        ans = max(ans, vs[i] - minVal);
    }

    return ans >= 0;
}

void solve() {
    for (int i = 1; i <= n; i++) va[i] *= 10000;

    ll left = 0, right = 2000 * 10000;
    while (left < right) {
        ll mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left / 10 << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%lld", &va[i]);
    solve();

    return 0;
}

