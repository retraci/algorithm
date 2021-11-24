#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

ll a, b, c, d, n;
vector<ll> vg[55];

ll get_g(ll x) {
    ll res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }

    return res;
}

ll cal(ll x, ll g) {
    return a * x * x * g + b * x * x + c * x * g * g + d * x * g;
}

void init() {
    for (int i = 1; i <= 1e6; i++) {
        ll g = get_g(i);
        vg[g].push_back(i);
    }
}

void solve() {
    ll ans = 1e18;
    for (int g = 1; g <= 54; g++) {
        int left = 0, right = upper_bound(vg[g].begin(), vg[g].end(), n) - vg[g].begin() - 1;
        if (left > right) continue;

        int A = a * g + b;
        if (A <= 0) {
            ans = min({ans, cal(vg[g][left], g), cal(vg[g][right], g)});
            continue;
        }
        while (left <= right) {
            int lmid = left + (right - left) / 3, rmid = right - (right - left) / 3;
            ll lx = vg[g][lmid], rx = vg[g][rmid];
            ll ly = cal(lx, g), ry = cal(rx, g);
            if (ly > ry) left = lmid + 1;
            else right = rmid - 1;
            ans = min({ans, ly, ry});
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    init();
    while (T--) {
        scanf("%lld%lld%lld%lld%lld", &a, &b, &c, &d, &n);
        solve();
    }

    return 0;
}