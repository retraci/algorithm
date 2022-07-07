#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

// region 自动取模类
template<int MOD, int RT>
struct mint {
    static const int mod = MOD;

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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 2e5 + 10;
const int MOD = 1e9 + 7;

using Z = mint<MOD, 5>;

int n, k;
Graph<N, N> g;
Binom<N, Z> binom;
int sz[N];
Z ans;

void dfs(int u, int fno) {
    sz[u] = 1;

    Z s = 0;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);

        sz[u] += sz[v];
        s += binom.C(sz[v], k);
    }

    s += binom.C(n - sz[u], k);
    ans += n * (binom.C(n, k) - s);

    if (fno != -1) {
        Z t = (binom.C(sz[u], k) - (s - binom.C(n - sz[u], k)));
        ans += Z(1) * sz[u] * (n - sz[u]) * t;
    }
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        Z t = binom.C(n - sz[v], k) - (s - binom.C(sz[v], k));
        ans += Z(1) * (n - sz[v]) * sz[v] * t;
    }
}

void solve() {
    dfs(1, -1);

    cout << ans << "\n";
}

void prework() {
    binom.init(2e5);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> k;
        g.init(n, n - 1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v), g.add(v, u);
        }
        solve();
    }

    return 0;
}