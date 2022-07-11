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
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

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
const int N = 2510;

int n;
string s;

void solve() {
    vector<int> one;
    one.push_back(1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') one.push_back(i);
    }
    one.push_back(n);

    int ans = 1;
    for (int i = 1, j = one.size() - 2; ; i++, j--) {
        if (j + 2 == i) break;
        if (j + 1 == i) {
            ans = 1LL * ans * ksm(2, one[i] - one[j]) % MOD;
            break;
        }

        int t = 0;
        int c1 = one[i] - one[i - 1], c2 = one[j + 1] - one[j];
        for (int k = 0; k <= min(c1, c2); k++) {
            t += 1LL * C(c1, k) * C(c2, k) % MOD;
            t %= MOD;
        }
        ans = 1LL * ans * t % MOD;
    }

    cout << ans << "\n";
}

void prework() {
    init_comb(2500);
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}