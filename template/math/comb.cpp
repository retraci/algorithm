// region comb
ll fac[N], ifac[N];

inline ll ksm(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll x) {
    return ksm(x, MOD - 2);
}

inline ll C(ll a, ll b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
}

inline void init_comb(int lim) {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= lim; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[lim] = inv(fac[lim]);
    for (int i = lim - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}
// endregion

// region lucas
inline ll ksm(ll a, ll b, ll p) {
    a %= p;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll x, ll p) {
    return ksm(x, p - 2, p);
}

inline ll C(ll a, ll b, ll p) {
    if (b > a) return 0;

    ll res = 1;
    for (int i = 1, j = a; i <= b; i++, j--) {
        res = res * j % p;
        res = res * inv(i, p) % p;
    }
    return res;
}

ll lucas(ll a, ll b, ll p) {
    if (a < p && b < p) return C(a, b, p);
    return 1LL * C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}
// endregion