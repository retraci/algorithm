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
using ai10 = array<int, 10>;
using node = pair<int, ai10>;
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 23;
const int MOD = 1e9 + 7;

int n, m;
node f[N];

void solve() {
    int ans = 0;
    while (n) {
        int x = n % 10;
        ans += f[m + x].fi;
        ans %= MOD;
        n /= 10;
    }
    cout << ans << "\n";
}

void prework() {
    f[0] = {1, {1}};
    for (int i = 1; i <= 2e5 + 10; i++) {
        auto [len, cnt] = f[i - 1];

        f[i].fi = (len + cnt[9]) % MOD;
        for (int k = 1; k <= 9; k++) f[i].se[k] = cnt[k - 1];

        f[i].se[1] += cnt[9];
        f[i].se[1] %= MOD;
        f[i].se[0] += cnt[9];
        f[i].se[0] %= MOD;
    }
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
        cin >> n >> m;
        solve();
    }

    return 0;
}