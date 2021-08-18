#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll L, T;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll euler(ll x) {
    ll res = x;

    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);

    return res;
}

ll qmulti(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }

    return res;
}

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = qmulti(res, a, mod);
        a = qmulti(a, a, mod);
        b >>= 1;
    }

    return res;
}

void solve () {
    ll d = gcd(8, L);
    ll n = 9 * L / d;

    ll ret = 1e18;
    ll phi = euler(n);
    for (ll i = 1; i * i <= phi; i++) {
        if (phi % i == 0) {
            ll a = i, b = phi / i;

            if (qpow(10, a, n) == 1) ret = min(ret, a);
            if (qpow(10, b, n) == 1) ret = min(ret, b);
        }
    }

    ret = ret == 1e18 ? 0 : ret;
    printf("Case %lld: %lld\n", ++T, ret);
}

int main() {
    freopen("../in.txt", "r", stdin);

    while (cin >> L, L) {
        solve();
    }

    return 0;
}