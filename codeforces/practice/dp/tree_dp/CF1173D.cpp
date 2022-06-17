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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int MOD = 998244353;
const int N = 2e5 + 10;
const int M = 2e5 + 10;

int n;
int du[N], fac[N];
int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int dfs(int u, int fno) {
    int res = fac[du[u]];

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        res = 1LL * res * dfs(v, u) % MOD;
    }

    return res;
}

void solve() {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;

    int ans = dfs(1, 0);

    ans = 1LL * n * ans % MOD;
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
            du[u]++, du[v]++;
        }
        solve();
    }

    return 0;
}