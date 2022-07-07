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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

using Z = mint<MOD, 5>;

int n;
int a[N];

void solve() {
    vector<Z> s(n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    vector<pii> b;
    for (int len = 1; len <= (n + 1) / 2; len++) {
        int L = len, R = n - len + 1;
        b.push_back({L, R});
    }

    Z ans = 0, sum = 0, len = 1;
    for (auto [L, R] : b) {
        sum += s[R] - s[L - 1];
        ans += sum / len, len += 1;
    }
    if (~n & 1) b.push_back({2, 1});

    reverse(b.begin(), b.end());
    for (auto [L, R] : b) {
        sum -= s[R] - s[L - 1];
        ans += sum / len, len += 1;
    }

    cout << ans << "\n";
}

void prework() {
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}