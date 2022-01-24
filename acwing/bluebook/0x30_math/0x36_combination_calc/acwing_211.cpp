#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 10007;

ll a, b, k, n, m;

ll qpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll C(ll k, ll n) {
    ll res = 1;
    for (ll i = 1, j = n; i <= k; i++, j--) {
        res = res * j % MOD * qpow(i, MOD - 2) % MOD;
    }
    return res;
}

void solve() {
    ll ans = qpow(a, n) * qpow(b, m) % MOD * C(n, k) % MOD;
    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> a >> b >> k >> n >> m;
    solve();

    return 0;
}