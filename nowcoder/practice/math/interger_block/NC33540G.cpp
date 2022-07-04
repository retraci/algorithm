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

const int MOD = 998244353;

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

int calc(int x) {
    static int inv6 = inv(6);
    return 1LL * x * (x + 1) % MOD * (2 * x + 1) % MOD * inv6 % MOD;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int n;

int get(int L, int R) {
    return (calc(R) - calc(L - 1)) % MOD;
}

void solve() {
    int ans = calc(n);
    int ed = n - 1;
    for (int L = 1; L <= ed; L++) {
        int t = (n - 1) / L;
        int R = min(ed, (n - 1) / t);

        int s = get(L, R);
        ans += 1LL * t * s % MOD;
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
    cin >> _;
    while (_--) {
        cin >> n;
        solve();
    }

    return 0;
}