#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

ll n, m;
ll va[N];

bool check(ll mid) {
    ll res = 0;

    for (int i = 1; i <= n; i++) {
        ll lb = va[i], rb = min(va[i] + mid - 1, va[i + 1] - 1);
        res += rb - lb + 1;
    }

    return res >= m;
}

void solve() {
    va[n + 1] = 1e18;

    ll left = 0, right = 1e18;
    while (left < right) {
        ll mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}