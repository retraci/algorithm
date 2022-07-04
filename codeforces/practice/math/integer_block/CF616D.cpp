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

const int MOD = 1e9 + 7;

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

int calc(ll L, ll R) {
    static int inv2 = inv(2);

    int t1 = (L + R) % MOD, t2 = (R - L + 1) % MOD;
    return 1LL * t1 * t2 % MOD * inv2 % MOD;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

using i128 = __int128;

ll n, m;

void solve() {
    int ans = i128(1) * n * m % MOD;
    ll ed = min(n, m);
    for (ll L = 1; L <= ed; L++) {
        ll t = n / L;
        ll R = min(ed, n / t);

        int sum = calc(L, R);
        int k = t % MOD;
        ans -= 1LL * sum * k % MOD;
        ans %= MOD;

        L = R;
    }

    ans = (ans + MOD) % MOD;
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
        cin >> n >> m;
        solve();
    }

    return 0;
}