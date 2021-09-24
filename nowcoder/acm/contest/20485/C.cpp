#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

#define ll long long

ll n;
unordered_map<ll, ll> f;

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }

    return res;
}

ll dfs(ll x) {
    if (x < 6) return x;
    if (f.count(x)) return f[x];
    ll cnt6 = 0, cnt9 = 0;
    for (ll cur = 1; cur <= x; cur *= 6, cnt6++);
    cnt6--;
    for (ll cur = 1; cur <= x; cur *= 9, cnt9++);
    cnt9--;

    f[x] = min(dfs(x - qpow(6, cnt6)), dfs(x - qpow(9, cnt9))) + 1;
    if (cnt9 - 1 >= 0) f[x] = min(f[x], dfs(x - qpow(9, max(0LL, cnt9 - 1))) + 1);
//    if (cnt6 - 1 >= 0) f[x] = min(f[x], dfs(x - qpow(6, max(0LL, cnt6 - 1))) + 1);

    return f[x];
}

void solve() {
    cout << dfs(n) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}