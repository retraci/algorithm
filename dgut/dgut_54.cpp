#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll a, b;

ll get_sum(ll x) {
    if (x == 0 || x == 1) return 0;
    ll res = 1;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            ll xa = i, xb = x / xa;
            if (xa == xb) res += xa;
            else res += xa + xb;
        }
    }

    return res;
}

void solve() {
    ll sa = get_sum(a), sb = get_sum(b);

    if (sa == b && sb == a) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b;
        solve();
    }

    return 0;
}