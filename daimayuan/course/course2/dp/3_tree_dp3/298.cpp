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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 110;
const int MOD = 1e9 + 7;

int n, m;
int g[N][N];

void solve() {
    if (m == 2) {
        cout << n * (n - 1) / 2 << "\n";
        return;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    int cnt[n + 1], f[m + 1];
    int ans = 0;
    for (int rt = 1; rt <= n; rt++) {
        for (int d = 1; d <= n; d++) {
            for (int i = 1; i <= n; i++) cnt[i] = 0;
            for (int i = 1; i <= n; i++) {
                if (g[rt][i] != 1) continue;
                for (int j = 1; j <= n; j++) {
                    if (g[rt][j] == d && g[rt][j] == g[rt][i] + g[i][j]) cnt[i]++;
                }
            }

            for (int i = 0; i <= m; i++) f[i] = 0;
            f[0] = 1;
            for (int i = 1; i <= n; i++) {
                if (cnt[i] == 0) continue;

                for (int j = m; j >= 1; j--) {
                    f[j] += 1LL * f[j - 1] * cnt[i] % MOD;
                    f[j] %= MOD;
                }
            }
            ans += f[m];
            ans %= MOD;
        }
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
    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = i == j ? 0 : 1e9;
            }
        }
        for (int i = 2; i <= n; i++) {
            int u, v;
            cin >> u >> v;
            g[u][v] = g[v][u] = 1;
        }

        solve();
    }

    return 0;
}