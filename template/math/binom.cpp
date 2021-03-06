// region 自动取模类
template<int MOD, int RT>
struct mint {
    static constexpr mint rt() { return RT; } // primitive root for FFT
    int v;

    explicit operator int() const { return v; } // explicit -> don't silently convert to int
    mint() : v(0) {}

    mint(ll _v) {
        v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD;
    }

    bool operator==(const mint &o) const {
        return v == o.v;
    }

    friend bool operator!=(const mint &a, const mint &b) {
        return !(a == b);
    }

    friend bool operator<(const mint &a, const mint &b) {
        return a.v < b.v;
    }

    mint &operator+=(const mint &o) {
        if ((v += o.v) >= MOD) v -= MOD;
        return *this;
    }

    mint &operator-=(const mint &o) {
        if ((v -= o.v) < 0) v += MOD;
        return *this;
    }

    mint &operator*=(const mint &o) {
        v = int((ll) v * o.v % MOD);
        return *this;
    }

    mint &operator/=(const mint &o) { return (*this) *= inv(o); }

    friend mint pow(mint a, ll p) {
        mint ans = 1;
        assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
        return ans;
    }

    friend mint inv(const mint &a) {
        assert(a.v != 0);
        return pow(a, MOD - 2);
    }

    mint operator-() const { return mint(-v); }

    mint &operator++() { return *this += 1; }

    mint &operator--() { return *this -= 1; }

    friend mint operator+(mint a, const mint &b) { return a += b; }

    friend mint operator-(mint a, const mint &b) { return a -= b; }

    friend mint operator*(mint a, const mint &b) { return a *= b; }

    friend mint operator/(mint a, const mint &b) { return a /= b; }

    friend std::istream &operator>>(std::istream &is, mint &a) {
        ll tv;
        is >> tv;
        a = mint(tv);
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const mint &a) {
        return os << a.v;
    }
};
// endregion

// region Binom(Z)
template<int N, class Z>
struct Binom {
    Z fac[N + 10], ifac[N + 10];

    Binom() {}

    void init(int lim) {
        fac[0] = ifac[0] = 1;
        for (int i = 1; i <= lim; i++) fac[i] = 1LL * fac[i - 1] * i;
        ifac[lim] = inv(fac[lim]);
        for (int i = lim - 1; i >= 1; i--) ifac[i] = 1LL * ifac[i + 1] * (i + 1);
    }

    Z C(int a, int b) {
        if (a < 0 || b < 0 || a < b) return 0;
        return fac[a] * ifac[b] * ifac[a - b];
    }
};
// endregion

// region Binom
template<int N, int MOD>
struct Binom {
    int fac[N + 10], ifac[N + 10];

    Binom() {}

    void init(int lim) {
        fac[0] = ifac[0] = 1;
        for (int i = 1; i <= lim; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
        ifac[lim] = inv(fac[lim]);
        for (int i = lim - 1; i >= 1; i--) ifac[i] = 1LL * ifac[i + 1] * (i + 1) % MOD;
    }

    int ksm(ll a, ll b) {
        a %= MOD;
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    int inv(ll x) {
        return ksm(x, MOD - 2);
    }

    int C(int a, int b) {
        if (a < 0 || b < 0 || a < b) return 0;
        return 1LL * fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
    }
};
// endregion

// region lucas 固定 P
vector<ll> fac, ifac;

ll ksm(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return ksm(x, MOD - 2);
}

ll C(ll a, ll b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
}

void init_comb(int lim) {
    fac.resize(lim + 1), ifac(lim + 1);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= lim; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[lim] = inv(fac[lim]);
    for (int i = lim - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}

ll lucas(ll a, ll b) {
    if (a < MOD && b < MOD) return C(a, b);
    return 1LL * C(a % MOD, b % MOD) * lucas(a / MOD, b / MOD) % MOD;
}
// endregion

// region lucas 非固定 P
ll ksm(ll a, ll b, ll p) {
    a %= p;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll inv(ll x, ll p) {
    return ksm(x, p - 2, p);
}

ll C(ll a, ll b, ll p) {
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
