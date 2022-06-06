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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 55;

int n, m, k;
int a[N];
int p[N];
int fac[N], ifac[N];

void init() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= k; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
    ifac[k] = inv(fac[k]);
    for (int i = k - 1; i >= 1; i--) ifac[i] = 1LL * ifac[i + 1] * (i + 1) % MOD;

    int tt = accumulate(a + 1, a + n + 1, 0);
    int itt = inv(tt);
    for (int i = 1; i <= n; i++) p[i] = 1LL * a[i] * itt % MOD;
}

void solve() {
    init();

    int f[n + 3][n + 3][k + 3];
    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int l = 0; l <= k; l++) {
                for (int c = 0; c <= k - l; c++) {
                    f[i][j + (c != 0)][l + c] += 1LL * f[i - 1][j][l] * inv(fac[c]) % MOD * ksm(p[i], c) % MOD;
                    f[i][j + (c != 0)][l + c] %= MOD;
                }
            }
        }
    }

    int ans = 1LL * fac[k] * f[n][m][k] % MOD;
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
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}