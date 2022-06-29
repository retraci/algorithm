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

    int ksm(int a, int b) {
        a %= MOD;
        int res = 1;
        while (b) {
            if (b & 1) res = 1LL * res * a % MOD;
            a = 1LL * a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    int inv(int x) {
        return ksm(x, MOD - 2);
    }

    int C(int a, int b) {
        if (a < 0 || b < 0 || a < b) return 0;
        return 1LL * fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1010;
const int MOD = 1e9 + 7;

ll n, l, r, z;
Binom<N, MOD> binom;

int calc(ll x) {
    static int f[2 * N], pf[2 * N], tmp[2 * N];

    fill(f, f + 2 * n + 1, 0);
    f[0] = 1;
    for (int k = 60; k >= 0; k--) {
        swap(pf, f);
        fill(f, f + 2 * n + 1, 0);
        fill(tmp, tmp + 2 * n + 1, 0);

        for (int i = 0; i <= 2 * n; i++) {
            int ns = min(2 * n, i * 2 + (x >> k & 1));
            tmp[ns] += pf[i];
            tmp[ns] %= MOD;
        }

        for (int i = 0; i <= 2 * n; i++) {
            for (int j = z >> k & 1; j <= n; j += 2) {
                if (i - j >= 0) {
                    f[i - j] += 1LL * tmp[i] * binom.C(n, j) % MOD;
                    f[i - j] %= MOD;
                }
            }
        }
    }

    int res = 0;
    for (int i = 0; i <= 2 * n; i++) {
        res += f[i];
        res %= MOD;
    }
    return res;
}

void solve() {
    int ans = calc(r) - calc(l - 1);
    ans = ((ans % MOD) + MOD) % MOD;
    cout << ans << "\n";
}

void prework() {
    binom.init(1e3);
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
        cin >> n >> l >> r >> z;
        solve();
    }

    return 0;
}