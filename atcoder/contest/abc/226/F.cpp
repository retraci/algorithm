#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cassert>
#include <random>
#include <cmath>

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
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int MOD = 998244353;

// region comb
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
    fac.resize(lim + 1), ifac.resize(lim + 1);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= lim; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[lim] = inv(fac[lim]);
    for (int i = lim - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 55;

int n, k;

int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

int lcm(int a, int b) {
    return a * b / __gcd(a, b);
}

void solve() {
    map<int, int> f[n + 1];
    f[0][1] = 1;
    for (int i = 0; i <= n; i++) {
        for (auto [p, c] : f[i]) {
            for (int j = 1; i + j <= n; j++) {
                int ns = lcm(p, j);
                f[i + j][ns] += c * C(n - i - 1, j - 1) % MOD * fac[j - 1] % MOD;
                f[i + j][ns] %= MOD;
            }
        }
    }

    int ans = 0;
    for (auto [p, c] : f[n]) {
        ans += 1LL * c * ksm(p, k) % MOD;
        ans %= MOD;
    }
    cout << ans << "\n";
}

void prework() {
    init_comb(50);
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
        solve();
    }

    return 0;
}