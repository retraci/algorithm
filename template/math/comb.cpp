// region comb

const ll MOD = 998244353;
const int N = 5010;

ll fac[N], ifac[N];

inline ll qsm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll x) {
    return qsm(x, MOD - 2);
}

inline ll C(ll a, ll b) {
    if (a < 0 || b < 0 || a - b < 0) return 0;
    return fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
}

inline void init_comb(int lim) {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= lim; i++) fac[i] = fac[i - 1] * i % MOD, ifac[i] = inv(fac[i]);
}
// endregion